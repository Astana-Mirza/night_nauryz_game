#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "panel_state.h"
#include "save_load_state.h"
#include "../interfaces/visitor.h"
#include "../ui/pause_panel.h"

class Game;

class PauseState : public PanelState {
public:
	PauseState(Game& g, const std::shared_ptr<Visitor>& sv);
	void save_menu();
	void load_menu();
	void quit();

private:
	std::shared_ptr<Visitor> saver;
};

#endif
