#include "../../inc/states/main_menu_state.h"

MainMenuState::MainMenuState(Game& g) : PanelState::PanelState(g) {
	ConfigManager::instance().difficulty = Difficulty::Easy;
	panel = std::make_unique<MainMenuPanel>(*(game.get_painter()), *this);
}


void MainMenuState::close() {
	game.get_painter()->pop_panel();
	game.exit();
}


void MainMenuState::start_game() {
	StandardBuilder builder{game};
	if (builder.load("levels/level1.txt")) {
		game.get_painter()->clear();
		game.get_painter()->apply_preload();
		game.push_state(builder.get_result(), true);
	}

}


void MainMenuState::load_game() {
	auto load = std::make_unique<SaveLoadState>(game);
	game.push_state(std::move(load));
}

void MainMenuState::set_difficulty(const std::string& diff) {
	if (diff == "Easy")
		ConfigManager::instance().difficulty = Difficulty::Easy;
	else if (diff == "Medium")
		ConfigManager::instance().difficulty = Difficulty::Medium;
	else if (diff == "Hard")
		ConfigManager::instance().difficulty = Difficulty::Hard;
	else
		throw std::runtime_error{"wrong difficulty"};
}
