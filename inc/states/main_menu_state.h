#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "panel_state.h"
#include "gameplay_state.h"
#include "save_load_state.h"
#include "../utility/config_manager.h"
#include "../utility/standard_builder.h"
#include "../ui/main_menu_panel.h"

class Game;

class MainMenuState : public PanelState {
public:
	MainMenuState(Game& g);
	void close();
	void start_game();
	void load_game();
	void set_difficulty(const std::string& diff);
};

#endif
