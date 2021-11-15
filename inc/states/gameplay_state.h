#ifndef GAMEPLAY_STATE_H
#define GAMEPLAY_STATE_H

#include <memory>
#include "panel_state.h"
#include "pause_state.h"
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
	GameplayState(Game& g,
			const std::shared_ptr<RenderEngine>& paint,
			const std::shared_ptr<ILogger>& log);
	void update(double delta);
	void game_over();
	void game_paused();
	void level_completed();

	void player_moved() { steps++; }
	void enemy_killed() { enemies_killed++; }
	void coin_picked() { coins_picked++; }

	size_t get_player_steps() const { return steps; }
	size_t get_killed_count() const { return enemies_killed; }
	size_t get_coin_count() const { return coins_picked; }

	Cell& get_cell(Point2D pos) const { return current_field.get_cell(pos); }
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
	size_t enemies_killed = 0;
	size_t steps = 0;
	size_t coins_picked = 0;
	std::shared_ptr<RenderEngine> painter;
	std::shared_ptr<ILogger> logger;
	std::unique_ptr<FieldBuilder> builder;
	std::set<std::shared_ptr<CellElement>> objects;
	Field current_field = Field{0, 0};
};


template <typename... Rules>
GameplayState<Rules...>::GameplayState(Game& g,
		const std::shared_ptr<RenderEngine>& paint,
		const std::shared_ptr<ILogger>& log) :
	game{g}, painter{paint}, logger{log}, current_field{16, 9} {
	command_handler = std::make_shared<GameplayCommandHandler>(*this);
	builder = std::make_unique<StandardBuilder>(*this, painter,
						logger, command_handler);
	builder->reset();
	builder->setup_cells();
	builder->spawn_items();
	builder->spawn_entities();
	current_field = std::move(builder->get_result());
	logger->write_log("LEVEL STARTED\n");
}


template <typename... Rules>
void GameplayState<Rules...>::update(double delta) {
	wait_time += delta;
	if (wait_time >= update_time) {
		for (auto& obj : objects) {	// update cell elementsя
			obj->update();
		}
		wait_time = 0;
	}
}


template <typename... Rules>
void GameplayState<Rules...>::game_over() {
	game.exit();	// will be removed
}


template <typename... Rules>
void GameplayState<Rules...>::game_paused() {
	auto pause = std::make_unique<PauseState>(game, painter);
	game.push_state(std::move(pause));
}


template <typename... Rules>
void GameplayState<Rules...>::level_completed() {
	if (check_all_rules(Rules{}...))
		game.exit();
}

#endif
