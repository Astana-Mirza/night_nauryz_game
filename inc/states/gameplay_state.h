#ifndef GAMEPLAY_STATE_H
#define GAMEPLAY_STATE_H

#define LEVEL1 "levels/level1.txt"

#include <memory>
#include "panel_state.h"
#include "pause_state.h"
#include "info_state.h"
#include "../game.h"
#include "../field.h"
#include "../interfaces/igameplay_manager.h"
#include "../interfaces/game_state.h"
#include "../input_commands/gameplay_command_handler.h"
#include "../utility/standard_builder.h"

class Game;

template <typename... Rules>
class GameplayState: public GameState, public IGameplayManager {
public:
	GameplayState(Game& g);
	void update(double delta);
	void load_field(const std::string& filename);

	void game_over() {
		exiting = true;
		auto info = std::make_unique<InfoState>(game, "Game over");
		game.push_state(std::move(info));
	}
	void game_paused() {
		auto pause = std::make_unique<PauseState>(game);
		game.push_state(std::move(pause));
	}
	void level_completed() {
		if (check_all_rules(Rules{}...)) {
			exiting = true;
			auto info = std::make_unique<InfoState>(game, "Victory!");
			game.push_state(std::move(info));
		}
	}

	void player_moved() { steps++; }
	void enemy_killed() { enemies_killed++; }
	void coin_picked() { coins_picked++; }

	size_t get_player_steps() const { return steps; }
	size_t get_killed_count() const { return enemies_killed; }
	size_t get_coin_count() const { return coins_picked; }

	Cell& get_cell(Point2D pos) const {
		return current_field.get_cell(pos);
	}
	void add_object(const std::shared_ptr<CellElement>& obj) {
		objects.insert(obj);
	}
	void object_expired(const std::shared_ptr<CellElement>& obj) {
		objects.erase(obj);
	}

private:
	bool check_all_rules(Rules... args) const {
		return (... && (args.check_rule(*this)));
	}

	Game& game;
	double update_time = 0.1;	// 1 update per this count of seconds
	double wait_time = 0;
	bool exiting = false;
	size_t enemies_killed;
	size_t steps;
	size_t coins_picked;
	std::unique_ptr<FieldBuilder> builder;
	std::set<std::shared_ptr<CellElement>> objects;
	Field current_field;
};


template <typename... Rules>
GameplayState<Rules...>::GameplayState(Game& g) : game{g} {
	command_handler = std::make_shared<GameplayCommandHandler>(*this);
	builder = std::make_unique<StandardBuilder>(*this, game.get_painter(),
				game.get_logger(), command_handler);
	load_field(LEVEL1);
	game.get_logger()->write_log("\tLEVEL STARTED\n");
}


template <typename... Rules>
void GameplayState<Rules...>::update(double delta) {
	if (exiting)
		game.to_main_menu();
	wait_time += delta;
	if (wait_time >= update_time) {
		for (auto& obj : objects) {	// update cell elementsя
			obj->update();
		}
		wait_time = 0;
	}
}


template <typename... Rules>
void GameplayState<Rules...>::load_field(const std::string& filename) {
	enemies_killed = 0;
	steps = 0;
	coins_picked = 0;
	objects = {};
	game.get_painter()->clear_field();
	builder->reset(LEVEL1);
	builder->setup_cells();
	builder->spawn_elements();
	current_field = std::move(builder->get_result());
}

#endif
