#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <map>
#include <stack>
#include "interfaces/game_state.h"
#include "logger/logger.h"
#include "logger/time_logger_decorator.h"
#include "render/sfml_engine.h"
#include "input_commands/sfml_window_handle.h"

class GameState;

class Game {
public:
	Game();
	void run();
	void exit();
	void push_state(std::unique_ptr<GameState>&& st, bool force=false);
	void pop_state();
	void to_main_menu();

private:
	bool game_on = false;
	std::unique_ptr<WindowHandle> window_input;
	std::shared_ptr<ILogger> logger;
	std::shared_ptr<RenderEngine> painter;
	std::stack<std::unique_ptr<GameState>> state_stack;
};

#endif
