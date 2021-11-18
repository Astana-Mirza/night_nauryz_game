/*#include "../../inc/states/gameplay_state.h"
#include "../../inc/states/pause_state.h"

#include "../../inc/cell_elements/main_character.h"

#include "../../inc/cell_elements/power_up.h"
#include "../../inc/cell_elements/healer.h"
#include "../../inc/cell_elements/shield.h"

#include "../../inc/cell_elements/regular_enemy.h"
#include "../../inc/cell_elements/support_enemy.h"
#include "../../inc/cell_elements/vampire_enemy.h"

#include "../../inc/strategies/strategy_right_left.h"
#include "../../inc/strategies/strategy_up_down.h"

#include "../../inc/cells/finish_cell.h"
#include "../../inc/cells/start_cell.h"

#define PLAYER_TEXTURE "res/player.png"
#define SLIME_TEXTURE "res/regular_enemy.png"
#define VAMPIRE_TEXTURE "res/vampire_enemy.png"
#define SUPPORT_TEXTURE "res/support_enemy.png"
#define HEART_TEXTURE "res/heart.png"
#define POWERUP_TEXTURE "res/power_up.png"
#define SHIELD_TEXTURE "res/shield.png"
#define CHESS_TEXTURE "res/chess.png"
#define GRASS_TEXTURE "res/grass.png"
#define BRICK_TEXTURE "res/brick.png"

GameplayState::GameplayState(Game& g,
		const std::shared_ptr<RenderEngine>& paint,
		const std::shared_ptr<ILogger>& log) :
	game{g}, painter{paint}, logger{log}, current_field{16, 9} {
	command_handler = std::make_shared<GameplayCommandHandler>(*this);
	//logger->set_console_output(true, true);
	painter->register_field(current_field);
	configure_field();
	spawn_entities();
	spawn_items();
	logger->write_log("LEVEL STARTED\n");
}


void GameplayState::configure_field() {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 9; j++) {
			bool wall = (i%5)>2 && (j%7)<4;
			if (wall) {
				current_field.set_cell({i, j},
					std::make_unique<Cell>(false));
				painter->register_cell({i, j}, BRICK_TEXTURE);
			} else {
				current_field.set_cell({i, j},
					std::make_unique<Cell>(true));
				painter->register_cell({i, j}, GRASS_TEXTURE);
			}
		}
	}
	current_field.set_cell({0, 8}, std::make_unique<StartCell>());
	current_field.set_cell({15, 0}, std::make_unique<FinishCell>(*this));
	painter->register_cell({0, 8}, CHESS_TEXTURE);
	painter->register_cell({15, 0}, CHESS_TEXTURE);
}


void GameplayState::spawn_items() {
	auto power_up = std::make_shared<PowerUp>(*this, 10, Point2D{2, 3});
	add_object(power_up, POWERUP_TEXTURE);
	power_up->subscribe(painter);
	//power_up->subscribe(logger);

	auto healer = std::make_shared<Healer>(*this, 10, Point2D{2, 4});
	add_object(healer, HEART_TEXTURE);
	healer->subscribe(painter);
	//healer->subscribe(logger);

	auto shield = std::make_shared<Shield>(*this, 10, Point2D{2, 5});
	add_object(shield, SHIELD_TEXTURE);
	shield->subscribe(painter);
	//shield->subscribe(logger);
}


void GameplayState::spawn_entities() {
	auto pl = std::make_shared<MainCharacter>(*this, 3, 2, 2, Point2D{0, 8});
	add_object(pl, PLAYER_TEXTURE);
	pl->subscribe(painter);
	pl->subscribe(logger);
	command_handler->set_next(pl->get_command_handler());

	auto e1 = std::make_shared<VampireEnemy>(*this, 6, 1, 3, Point2D{10, 7});
	add_object(e1, VAMPIRE_TEXTURE);
	e1->set_strategy(std::make_unique<StrategyUpDown>());
	e1->subscribe(painter);
	//e1->subscribe(logger);

	auto e2 = std::make_shared<RegularEnemy>(*this, 6, 3, 3, Point2D{3, 4});
	add_object(e2, SLIME_TEXTURE);
	e2->set_strategy(std::make_unique<StrategyRightLeft>());
	e2->subscribe(painter);
	e2->subscribe(logger);

	auto e3 = std::make_shared<SupportEnemy>(*this, 6, 5, 3, Point2D{11, 4});
	add_object(e3, SUPPORT_TEXTURE);
	e3->set_strategy(std::make_unique<StrategyUpDown>());
	e3->subscribe(painter);
	//e3->subscribe(logger);
}


void GameplayState::update(double delta) {
	wait_time += delta;
	if (wait_time >= update_time) {
		for (auto& obj : objects) {	// update cell elementsя
			obj->update();
		}
		wait_time = 0;
	}
}


void GameplayState::game_over() {
	game.exit();	// will be removed
}


void GameplayState::game_paused() {
	auto pause = std::make_unique<PauseState>(game, painter);
	game.push_state(std::move(pause));
}


void GameplayState::level_completed() {
	game.exit();	// will be removed
}


Cell& GameplayState::get_cell(Point2D pos) const {
	return current_field.get_cell(pos);
}


void GameplayState::object_expired(const std::shared_ptr<CellElement>& obj) {
	objects.erase(obj);
}


void GameplayState::add_object(const std::shared_ptr<CellElement>& obj,
		const std::string& texname) {
	objects.insert(obj);
	get_cell(obj->get_pos()).set_element(obj);
	painter->register_cell_element(*obj, texname);
}
*/
