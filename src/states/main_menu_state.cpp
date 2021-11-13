#include "../../inc/states/main_menu_state.h"
#include "../../inc/states/gameplay_state.h"

MainMenuState::MainMenuState(Game& g, const std::shared_ptr<RenderEngine>& render,
		const std::shared_ptr<ILogger>& log):
		PanelState::PanelState(g, render), logger{log} {
	panel = std::make_unique<MainMenuPanel>(*render, *this);
}

void MainMenuState::close() {
	painter->pop_panel();
	game.exit();
}


void MainMenuState::start_game() {
	painter->pop_panel();
	auto gameplay = std::make_unique<GameplayState>(game, painter, logger);
	game.push_state(std::move(gameplay));
}

void MainMenuState::set_difficulty(const std::string& diff) {
	difficulty = diff;
}
