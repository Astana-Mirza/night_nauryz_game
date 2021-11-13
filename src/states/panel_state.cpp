#include "../../inc/states/panel_state.h"

PanelState::PanelState(Game& g, const std::shared_ptr<RenderEngine>& render):
						game{g}, painter{render} {
	command_handler = std::make_unique<PanelCommandHandler>(*this);
}


void PanelState::close() {
	painter->pop_panel();
	game.pop_state();
}

UIPanel& PanelState::get_panel() const { return *panel; }
