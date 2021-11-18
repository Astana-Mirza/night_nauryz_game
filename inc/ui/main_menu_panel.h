#ifndef MAIN_MENU_PANEL_H
#define MAIN_MENU_PANEL_H

#include "../states/main_menu_state.h"
#include "base_panel.h"
#include "menu_button.h"

class MainMenuState;

class MainMenuPanel : public BasePanel {
public:
	MainMenuPanel(RenderEngine& render, MainMenuState& st);
	void notify(const std::string& event);

private:
	MainMenuState& state;
	size_t curr_diff = 0;
	std::vector<std::string> difficulties = {"Easy", "Medium", "Hard"};
};

#endif
