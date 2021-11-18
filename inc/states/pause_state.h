#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "panel_state.h"
#include "../ui/pause_panel.h"

class Game;

class PauseState : public PanelState {
public:
	PauseState(Game& g, const std::shared_ptr<RenderEngine>& render);
	void quit();
};

#endif
