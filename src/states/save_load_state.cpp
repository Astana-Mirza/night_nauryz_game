#include "../../inc/states/save_load_state.h"

SaveLoadState::SaveLoadState(Game& g, bool save) : PanelState::PanelState(g),
						saving{save} {
	panel = std::make_unique<SaveLoadPanel>(*(game.get_painter()), *this);
}


void SaveLoadState::save_or_load(size_t slot) {
	saving ? save(slot) : load(slot);
}


void SaveLoadState::save(size_t slot) {

}


void SaveLoadState::load(size_t slot) {

}
