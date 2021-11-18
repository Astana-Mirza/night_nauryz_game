#include "../../inc/states/main_menu_state.h"

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
	std::unique_ptr<GameState> gameplay;
	if (difficulty == "Easy") {
		gameplay = std::make_unique<GameplayState<
			CoinsPickedRule<1>
		>>(game, painter, logger);
	}
	else if (difficulty == "Medium") {
		gameplay = std::make_unique<GameplayState<
			CoinsPickedRule<1>,
			EnemiesKilledRule<2>>
		>(game, painter, logger);
	}
	else if (difficulty == "Hard") {
		gameplay = std::make_unique<GameplayState<
			CoinsPickedRule<1>,
			EnemiesKilledRule<3>,
			MaxStepsRule<40>>
		>(game, painter, logger);
	}
	else
		throw std::runtime_error{"wrong difficulty"};
	game.push_state(std::move(gameplay), true);
}

void MainMenuState::set_difficulty(const std::string& diff) {
	difficulty = diff;
}
