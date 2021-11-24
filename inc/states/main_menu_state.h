#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "panel_state.h"
#include "gameplay_state.h"
#include "../rules/coins_picked_rule.h"
#include "../rules/enemies_killed_rule.h"
#include "../rules/max_steps_rule.h"
#include "../utility/config_manager.h"
#include "../ui/main_menu_panel.h"

class Game;

class MainMenuState : public PanelState {
public:
	MainMenuState(Game& g);
	void close();
	void start_game();
	void set_difficulty(const std::string& diff);
};

#endif
