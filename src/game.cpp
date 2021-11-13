#include "../inc/game.h"
#include "../inc/states/main_menu_state.h"

Game::Game() {
	logger = std::make_shared<TimeLoggerDecorator>(
		std::make_unique<Logger>(true, true));
	auto win = std::make_shared<sf::RenderWindow>(sf::VideoMode(1366, 768),
				"Game", sf::Style::Fullscreen);
	painter = std::make_shared<SFMLEngine>(win);
	window_input = std::make_unique<SFMLWindowHandle>(win);
	to_main_menu();
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
}


void Game::exit() {
	game_on = false;
}


void Game::push_state(std::unique_ptr<GameState>&& st) {
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
}


void Game::to_main_menu() {
	state_stack = {};
	painter->clear_field();
	auto main_menu = std::make_unique<MainMenuState>(*this, painter, logger);
	window_input->set_command_handler(main_menu->get_command_handler());
	state_stack.push(std::move(main_menu));
}
