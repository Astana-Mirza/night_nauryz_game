#ifndef INFO_STATE_H
#define INFO_STATE_H

#include "panel_state.h"
#include "../ui/info_panel.h"

class Game;

class InfoState : public PanelState {
public:
	InfoState(Game& g, const std::string& info);
};

#endif
