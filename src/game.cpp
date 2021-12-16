#include "../inc/game.h"
#include "../inc/states/main_menu_state.h"

#define CONFIG_FILE "res/config.txt"
#define WINDOW_NAME "Game"

Game::Game() {
	try {
	logger = std::make_shared<TimeLoggerDecorator>(
		std::make_unique<Logger>(true, true, "log.txt"));
	} catch(GameError& e) {
		std::exit(1);
	}
	try {
		ConfigManager::instance().read_config(CONFIG_FILE);
		auto win = std::make_shared<sf::RenderWindow>(
			sf::VideoMode(1366, 768), WINDOW_NAME,
			sf::Style::Fullscreen);
		painter = std::make_shared<SFMLEngine>(win);
				window_input = std::make_unique<SFMLWindowHandle>(win);
		to_main_menu();
	} catch(GameError& e) {
		logger->write_log("Critical error: " + e.what() + "\nAborting\n");
		std::exit(1);
	}
}


void Game::run() {
	game_on = true;
	auto stamp = std::chrono::steady_clock::now();
	auto now = stamp;
	std::chrono::duration<double> elapsed_seconds = now-stamp;
	while (game_on) {
		stamp = std::chrono::steady_clock::now();
		window_input->process_commands();
		if (!state_stack.empty())
			state_stack.top()->update(elapsed_seconds.count());
		painter->render_frame();
		now = std::chrono::steady_clock::now();
		elapsed_seconds = now - stamp;
	}
	painter->clear();
}


void Game::exit() {
	game_on = false;
}


void Game::push_state(std::unique_ptr<GameState>&& st, bool force) {
	if (force) {
		state_stack = {};
	}
	state_stack.push(std::move(st));
	window_input->set_command_handler(
				state_stack.top()->get_command_handler());
}


void Game::pop_state() {
	if (state_stack.empty())
		throw std::runtime_error{"game state stack is empty"};
	state_stack.pop();
	if (!state_stack.empty())
		window_input->set_command_handler(
				state_stack.top()->get_command_handler());
	else
		window_input->set_command_handler(nullptr);
}


void Game::to_main_menu() {
	state_stack = {};
	painter->clear();
	auto main_menu = std::make_unique<MainMenuState>(*this);
	window_input->set_command_handler(main_menu->get_command_handler());
	state_stack.push(std::move(main_menu));
}

std::shared_ptr<ILogger> Game::get_logger() const { return logger; }
std::shared_ptr<RenderEngine> Game::get_painter() const { return painter; }
