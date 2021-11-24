#include "../../inc/utility/standard_builder.h"

StandardBuilder::StandardBuilder(IGameplayManager& gm,
		const std::shared_ptr<RenderEngine>& paint,
		const std::shared_ptr<ILogger>& log,
		const std::shared_ptr<CommandHandler>& ch) : gameplay{gm},
		 	painter{paint}, logger{log}, command_handler{ch} {}


void StandardBuilder::reset(const std::string& saved_level) {
	painter->clear_field();
	current_field = Field{16, 9};
	painter->register_field(current_field);
}


void StandardBuilder::setup_cells() {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 9; j++) {
			bool wall = (i%5)>2 && (j%7)<4;
			if (wall) {
				current_field.set_cell({i, j},
					std::make_unique<Cell>(false));
				painter->register_cell({i, j},
					ConfigManager::instance().res_name(
							"brick_texture"));
			} else {
				current_field.set_cell({i, j},
					std::make_unique<Cell>(true));
				painter->register_cell({i, j},
					ConfigManager::instance().res_name(
							"grass_texture"));
			}
		}
	}
	current_field.set_cell({0, 8}, std::make_unique<StartCell>());
	current_field.set_cell({15, 0}, std::make_unique<FinishCell>(gameplay));
	painter->register_cell({0, 8},
		ConfigManager::instance().res_name("chess_texture"));
	painter->register_cell({15, 0},
		ConfigManager::instance().res_name("chess_texture"));
}


void StandardBuilder::spawn_elements() {
	auto power_up = std::make_shared<PowerUp>(gameplay, 10, Point2D{2, 3});
	add_object(power_up, ConfigManager::instance().res_name("powerup_texture"));
	power_up->subscribe(painter);
	//power_up->subscribe(logger);

	auto healer = std::make_shared<Healer>(gameplay, 10, Point2D{2, 4});
	add_object(healer, ConfigManager::instance().res_name("heart_texture"));
	healer->subscribe(painter);
	//healer->subscribe(logger);

	auto shield = std::make_shared<Shield>(gameplay, 10, Point2D{2, 5});
	add_object(shield, ConfigManager::instance().res_name("shield_texture"));
	shield->subscribe(painter);
	//shield->subscribe(logger);

	auto coin = std::make_shared<Coin>(gameplay, Point2D{0, 4});
	add_object(coin, ConfigManager::instance().res_name("coin_texture"));
	coin->subscribe(painter);

	auto pl = std::make_shared<MainCharacter>(gameplay, 3, 2, 2, Point2D{0, 8});
	add_object(pl, ConfigManager::instance().res_name("player_texture"));
	pl->subscribe(painter);
	pl->subscribe(logger);
	command_handler->set_next(pl->get_command_handler());

	auto e1 = std::make_shared<VampireEnemy>(gameplay, 6, 1, 3, Point2D{10, 7});
	add_object(e1, ConfigManager::instance().res_name("vampire_texture"));
	e1->set_strategy(std::make_unique<StrategyUpDown>());
	e1->subscribe(painter);
	//e1->subscribe(logger);

	auto e2 = std::make_shared<RegularEnemy>(gameplay, 6, 3, 3, Point2D{3, 4});
	add_object(e2, ConfigManager::instance().res_name("slime_texture"));
	e2->set_strategy(std::make_unique<StrategyRightLeft>());
	e2->subscribe(painter);
	e2->subscribe(logger);

	auto e3 = std::make_shared<SupportEnemy>(gameplay, 6, 5, 3, Point2D{11, 4});
	add_object(e3, ConfigManager::instance().res_name("support_texture"));
	e3->set_strategy(std::make_unique<StrategyUpDown>());
	e3->subscribe(painter);
	//e3->subscribe(logger);
}


void StandardBuilder::add_object(const std::shared_ptr<CellElement>& obj,
				const std::string& texture) {
	current_field.get_cell(obj->get_pos()).set_element(obj);
	painter->register_cell_element(*obj, texture);
	gameplay.add_object(obj);
}


Field&& StandardBuilder::get_result() {
	return std::move(current_field);
}
