#include "../../inc/states/info_state.h"

InfoState::InfoState(Game& g, const std::string& info):
					PanelState::PanelState{g} {
	panel = std::make_unique<InfoPanel>(*(game.get_painter()), *this, info);
}
