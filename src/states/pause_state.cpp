#include "../../inc/states/pause_state.h"

PauseState::PauseState(Game& g, const std::shared_ptr<RenderEngine>& render):
				PanelState::PanelState(g, render) {
	panel = std::make_unique<PausePanel>(*render, *this);
}

void PauseState::quit() {
	painter->pop_panel();
	game.to_main_menu();
}
