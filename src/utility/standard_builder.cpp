#include "../../inc/utility/standard_builder.h"
#include "../../inc/states/gameplay_state.h"

StandardBuilder::StandardBuilder(Game& gm) : game{gm}, line_num{0} {}


bool StandardBuilder::load(const std::string& saved_level) {
	current_filename = saved_level;
	infile.open(current_filename);
	try {
		if (!infile.is_open()) {
			throw FileError{"unable to open file", current_filename};
		}
		read_header();
	} catch(ParseError& e) {
		game.get_painter()->clear_preload_field();
		auto info = std::make_unique<InfoState>(game,
				"Parse error: " + e.what() + '\n' + e.get_filename()
				+ ": line " + std::to_string(e.get_line_num()));
		game.push_state(std::move(info));
		return false;
	} catch(FileError& e) {
		game.get_painter()->clear_preload_field();
		auto info = std::make_unique<InfoState>(game,
				"File error: " + e.what() + '\n' + e.get_filename());
		game.push_state(std::move(info));
		return false;
	} catch(WallError& e) {
		game.get_painter()->clear_preload_field();
		auto info = std::make_unique<InfoState>(game,
				"Wall error: " + e.what() + '\n');
		game.push_state(std::move(info));
		return false;
	} catch(GameError& e) {
		game.get_painter()->clear_preload_field();
		auto info = std::make_unique<InfoState>(game,
				"Game error: " + e.what() + '\n');
		game.push_state(std::move(info));
		return false;
	}
	return true;
}

void StandardBuilder::read_header() {
	read_line();
	bool set_diff;
	size_t width, height, enemies_killed, steps, coins_picked;
	if(!(current_line >> set_diff))
		throw ParseError{"unable to read set_diff",
				current_filename, line_num};
	if (set_diff) {
		size_t diff;
		if (!(current_line >> diff))
			throw ParseError{"unable to read difficulty",
					current_filename, line_num};
		ConfigManager::instance().difficulty =
			static_cast<Difficulty>(diff);
	}
	if (!(current_line >> enemies_killed >> steps >> coins_picked))
		throw ParseError{"unable to read statistics",
				current_filename, line_num};
	if (!(current_line >> height >> width))
		throw ParseError{"unable to read field size",
				current_filename, line_num};
	current_field = Field{width, height};
	game.get_painter()->clear_preload_field();
	game.get_painter()->register_field(current_field);

	switch (ConfigManager::instance().difficulty) {
		case Difficulty::Easy: {
			auto st = std::make_unique<GameplayState<
				CoinsPickedRule<1>
			>>(game, enemies_killed, steps, coins_picked);
			load_cells(*st, *st->get_command_handler());
			state = std::move(st);
		}
		break;
		case Difficulty::Medium: {
			auto st = std::make_unique<GameplayState<
				CoinsPickedRule<1>,
				EnemiesKilledRule<2>>
			>(game, enemies_killed, steps, coins_picked);
			load_cells(*st, *st->get_command_handler());
			state = std::move(st);
		}
		break;
		case Difficulty::Hard: {
			auto st = std::make_unique<GameplayState<
				CoinsPickedRule<1>,
				EnemiesKilledRule<3>,
				MaxStepsRule<40>>
			>(game, enemies_killed, steps, coins_picked);
			load_cells(*st, *st->get_command_handler());
			state = std::move(st);
		}
		break;
	}
}


void StandardBuilder::load_cells(IGameplayManager& st, CommandHandler& ch) {
	int width = current_field.get_width();
	int height = current_field.get_height();
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			read_line();
			std::unique_ptr<Cell> cell_ptr;
			std::string cell;
			bool passable, has_element;
			if (!(current_line >> cell >> passable >> has_element))
				throw ParseError{"unable to read cell",
						current_filename, line_num};
			if (!passable && has_element) {
				throw WallError{"element in wall"};
			}
			if (cell == "Cell") {
				cell_ptr = std::make_unique<Cell>(passable);
				if (passable) {
					game.get_painter()->register_cell({i, j},
						ConfigManager::instance().res_name(
							"grass_texture"));
				} else {
					game.get_painter()->register_cell({i, j},
						ConfigManager::instance().res_name(
							"brick_texture"));
				}
			} else if (cell == "StartCell") {
				if (!passable) {
					throw WallError{"start cell is wall"};
				}
				cell_ptr = std::make_unique<StartCell>();
				game.get_painter()->register_cell({i, j},
					ConfigManager::instance()
						.res_name("chess_texture"));
			} else if (cell == "FinishCell") {
				if (!passable) {
					throw WallError{"finish cell is wall"};
				}
				cell_ptr = std::make_unique<FinishCell>(st);
				game.get_painter()->register_cell({i, j},
					ConfigManager::instance()
						.res_name("chess_texture"));
			} else {
				throw ParseError{"unknown cell type",
						current_filename, line_num};
			}
			current_field.set_cell({i, j}, std::move(cell_ptr));
			if (has_element)
				spawn_element(st, ch, {i, j});
		}
	}
	st.set_field(std::move(current_field));
}


void StandardBuilder::read_characteristics(int& hp, int& armor,
				int& power, bool& has_strategy, bool strat) {
	if (!(current_line >> hp >> armor >> power))
			throw ParseError{"unable to read element characteristic",
			current_filename, line_num};
	if (strat && !(current_line >> has_strategy))
			throw ParseError{"unable to read has_strategy value",
			current_filename, line_num};
	if (hp <= 0 || armor < 0 || power < 0)
			throw GameError{"wrong entity characteristic"};
}


void StandardBuilder::spawn_element(IGameplayManager& st,
					CommandHandler& ch, Point2D pos) {
	std::string element;
	int hp, armor, power;
	int charact;
	bool has_strategy;
	if (!(current_line >> element))
		throw ParseError{"unable to read element type",
				current_filename, line_num};
	if (element == "MainCharacter") {
		read_characteristics(hp, armor, power, has_strategy, false);
		auto pl = std::make_shared<MainCharacter>(st, hp, armor,
								power, pos);
		add_object(st, pl,
			ConfigManager::instance().res_name("player_texture"));
		pl->subscribe(game.get_painter());
		pl->subscribe(game.get_logger());
		ch.set_next(pl->get_command_handler());

	} else if (element == "RegularEnemy") {
		read_characteristics(hp, armor, power, has_strategy, true);
		auto enemy = std::make_shared<RegularEnemy>(st, hp, armor,
								power, pos);
		add_object(st, enemy,
			ConfigManager::instance().res_name("slime_texture"));
		if (has_strategy)
			enemy->set_strategy(read_strategy());
		enemy->subscribe(game.get_painter());
	} else if (element == "SupportEnemy") {
		read_characteristics(hp, armor, power, has_strategy, true);
		auto enemy = std::make_shared<SupportEnemy>(st, hp, armor,
								power, pos);
		add_object(st, enemy,
			ConfigManager::instance().res_name("support_texture"));
		if (has_strategy)
			enemy->set_strategy(read_strategy());
		enemy->subscribe(game.get_painter());
	} else if (element == "VampireEnemy") {
		read_characteristics(hp, armor, power, has_strategy, true);
		auto enemy = std::make_shared<VampireEnemy>(st, hp, armor,
								power, pos);
		add_object(st, enemy,
			ConfigManager::instance().res_name("vampire_texture"));
		if (has_strategy)
			enemy->set_strategy(read_strategy());
		enemy->subscribe(game.get_painter());
	} else if (element == "Healer") {
		if (!(current_line >> charact))
			throw ParseError{"unable to read element characteristic",
					current_filename, line_num};
		auto healer = std::make_shared<Healer>(st, charact, pos);
		add_object(st, healer,
			ConfigManager::instance().res_name("heart_texture"));
		healer->subscribe(game.get_painter());
	} else if (element == "Shield") {
		if (!(current_line >> charact))
			throw ParseError{"unable to read element characteristic",
					current_filename, line_num};
		auto shield = std::make_shared<Shield>(st, charact, pos);
		add_object(st, shield,
			ConfigManager::instance().res_name("shield_texture"));
		shield->subscribe(game.get_painter());
	} else if (element == "PowerUp") {
		if (!(current_line >> charact))
			throw ParseError{"unable to read element characteristic",
					current_filename, line_num};
		auto power_up = std::make_shared<PowerUp>(st, charact, pos);
		add_object(st, power_up,
			ConfigManager::instance().res_name("powerup_texture"));
		power_up->subscribe(game.get_painter());
	} else if (element == "Coin") {
		auto coin = std::make_shared<Coin>(st, pos);
		add_object(st, coin,
			ConfigManager::instance().res_name("coin_texture"));
		coin->subscribe(game.get_painter());
	} else {
		throw ParseError{"unknown cell element type",
				current_filename, line_num};
	}
}


std::unique_ptr<Strategy> StandardBuilder::read_strategy() {
	std::string name;
	bool direction;
	if (!(current_line >> name >> direction))
		throw ParseError{"unable to read strategy",
				current_filename, line_num};
	if (name == "RL") {
		return std::make_unique<StrategyRightLeft>(direction);
	} else if (name == "UD") {
		return std::make_unique<StrategyUpDown>(direction);
	} else {
		throw ParseError{"unknown strategy type",
				current_filename, line_num};
	}
	return nullptr;
}


void StandardBuilder::add_object(IGameplayManager& st,
				const std::shared_ptr<CellElement>& obj,
				const std::string& texture) {
	current_field.get_cell(obj->get_pos()).set_element(obj);
	game.get_painter()->register_cell_element(*obj, texture);
	st.add_object(obj);
}


std::unique_ptr<GameState> StandardBuilder::get_result() {
	if (!state)
		throw GameError{"gameplay state is nullptr"};
	return std::move(state);
}


void StandardBuilder::read_line() {
	std::string line;
	if (!std::getline(infile, line))
		throw FileError{"unexpected end of file", current_filename};
	line_num++;
	current_line = std::stringstream{line};
}
