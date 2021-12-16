#include "../../inc/states/panel_state.h"

PanelState::PanelState(Game& g) : game{g} {
	command_handler = std::make_unique<PanelCommandHandler>(*this);
}


void PanelState::close() {
	game.get_painter()->pop_panel();
	game.pop_state();
}

UIPanel& PanelState::get_panel() const { return *panel; }
