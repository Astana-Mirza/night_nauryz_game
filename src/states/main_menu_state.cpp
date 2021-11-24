#include "../../inc/states/main_menu_state.h"

MainMenuState::MainMenuState(Game& g) : PanelState::PanelState(g) {
	panel = std::make_unique<MainMenuPanel>(*(game.get_painter()), *this);
}


void MainMenuState::close() {
	game.get_painter()->pop_panel();
	game.exit();
}


void MainMenuState::start_game() {
	game.get_painter()->pop_panel();
	std::unique_ptr<GameState> gameplay;
	switch (ConfigManager::instance().difficulty) {
		case Difficulty::Easy:
			gameplay = std::make_unique<GameplayState<
				CoinsPickedRule<1>
			>>(game);
		break;
		case Difficulty::Medium:
			gameplay = std::make_unique<GameplayState<
				CoinsPickedRule<1>,
				EnemiesKilledRule<2>>
			>(game);
		break;
		case Difficulty::Hard:
			gameplay = std::make_unique<GameplayState<
				CoinsPickedRule<1>,
				EnemiesKilledRule<3>,
				MaxStepsRule<40>>
			>(game);
		break;
	}
	game.push_state(std::move(gameplay), true);
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
