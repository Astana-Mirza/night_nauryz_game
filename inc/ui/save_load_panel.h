#ifndef SAVE_LOAD_PANEL_H
#define SAVE_LOAD_PANEL_H

#include "../states/save_load_state.h"
#include "base_panel.h"
#include "menu_button.h"

class SaveLoadState;

class SaveLoadPanel : public BasePanel {
public:
	SaveLoadPanel(RenderEngine& render, SaveLoadState& st);
	void notify(const std::string& event);

private:
	SaveLoadState& state;
};


#endif
