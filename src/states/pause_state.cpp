#include "../../inc/states/pause_state.h"

PauseState::PauseState(Game& g, const std::shared_ptr<Visitor>& sv):
			PanelState::PanelState(g), saver{sv} {
	panel = std::make_unique<PausePanel>(*(game.get_painter()), *this);
}


void PauseState::save_menu() {
	auto save = std::make_unique<SaveLoadState>(game, saver);
	game.push_state(std::move(save));
}


void PauseState::load_menu() {
	auto load = std::make_unique<SaveLoadState>(game);
	game.push_state(std::move(load));
}


void PauseState::quit() {
	game.get_painter()->pop_panel();
	game.to_main_menu();
}
