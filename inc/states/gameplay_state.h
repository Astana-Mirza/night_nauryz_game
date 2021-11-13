#ifndef GAMEPLAY_STATE_H
#define GAMEPLAY_STATE_H

#include <memory>
#include "../game.h"
#include "../field.h"
#include "../interfaces/igameplay_manager.h"
#include "../interfaces/game_state.h"
#include "../input_commands/gameplay_command_handler.h"

class Game;

class GameplayState: public GameState, public IGameplayManager {
public:
	GameplayState(Game& g,
			const std::shared_ptr<RenderEngine>& paint,
			const std::shared_ptr<ILogger>& log=nullptr);
	void update(double delta);
	void game_over();
	void game_paused();
	void level_completed();
	Cell& get_cell(Point2D pos) const;
	void object_expired(const std::shared_ptr<CellElement>& obj);
private:
	void configure_field();
	void spawn_items();
	void spawn_entities();
	void add_object(const std::shared_ptr<CellElement>& obj,
			const std::string& texname);

	Game& game;
	double update_time = 0.2;	// 1 update per this count of seconds
	double wait_time = 0;
	std::shared_ptr<RenderEngine> painter;
	std::shared_ptr<ILogger> logger;
	std::set<std::shared_ptr<CellElement>> objects;
	Field current_field;
};

#endif
