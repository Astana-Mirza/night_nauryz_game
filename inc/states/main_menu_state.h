#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "panel_state.h"
#include "../ui/main_menu_panel.h"

class Game;

class MainMenuState : public PanelState {
public:
	MainMenuState(Game& g, const std::shared_ptr<RenderEngine>& paint,
				const std::shared_ptr<ILogger>& log);
	void close();
	void start_game();
	void set_difficulty(const std::string& diff);

private:
	std::shared_ptr<ILogger> logger;
	std::string difficulty;
};

#endif
