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
#include "../utility/serial_file_visitor.h"

class Game;

template <typename... Rules>
class GameplayState: public GameState, public IGameplayManager {
public:
	GameplayState(Game& g, size_t killed=0, size_t step=0, size_t coins=0):
	game{g}, enemies_killed{killed}, steps{step}, coins_picked{coins} {
		command_handler =
			std::make_shared<GameplayCommandHandler>(*this);
	}

	void game_over() {
		exiting = true;
		auto info = std::make_unique<InfoState>(game, "Game over");
		game.push_state(std::move(info));
	}

	void level_completed() {
		if (check_all_rules(Rules{}...)) {
			exiting = true;
			auto info = std::make_unique<InfoState>(game, "Victory!");
			game.push_state(std::move(info));
		}
	}

	void set_field(Field&& field) { current_field = std::move(field); }

	void update(double delta);
	void game_paused();

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
	void load_next_level(const std::string& filename);
	bool check_all_rules(Rules... args) const {
		return (... && (args.check_rule(*this)));
	}

	Game& game;
	double update_time = 0.2;	// 1 update per this count of seconds
	double wait_time = 0;
	bool exiting = false;
	size_t enemies_killed;
	size_t steps;
	size_t coins_picked;
	std::set<std::shared_ptr<CellElement>> objects;
	Field current_field;
};


template <typename... Rules>
void GameplayState<Rules...>::game_paused() {
	auto saver = std::make_shared<SerialFileVisitor>(current_field,
			enemies_killed, steps, coins_picked);
	auto pause = std::make_unique<PauseState>(game, saver);
	game.push_state(std::move(pause));
}


template <typename... Rules>
void GameplayState<Rules...>::update(double delta) {
	if (exiting) {
		game.to_main_menu();
	} else {
		wait_time += delta;
		if (wait_time >= update_time) {
			for (auto& obj : objects) {	// update cell elements
				obj->update();
			}
			wait_time = 0;
		}
	}
}


template <typename... Rules>
void GameplayState<Rules...>::load_next_level(const std::string& filename) {
	StandardBuilder builder{game};
	if (builder.load(filename)) {
		game.get_painter()->clear();
		game.get_painter()->apply_preload();
		game.push_state(builder.get_result(), true);
	}
}

#endif
