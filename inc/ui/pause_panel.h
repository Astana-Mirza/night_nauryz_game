#ifndef PAUSE_PANEL_H
#define PAUSE_PANEL_H

#include "../states/pause_state.h"
#include "base_panel.h"
#include "menu_button.h"

class PauseState;

class PausePanel : public BasePanel {
public:
	PausePanel(RenderEngine& render, PauseState& st);
	void notify(const std::string& event);

private:
	PauseState& state;
};

#endif
