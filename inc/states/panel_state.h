#ifndef PANEL_STATE_H
#define PANEL_STATE_H

#include <memory>
#include "../interfaces/game_state.h"
#include "../interfaces/ui_panel.h"
#include "../input_commands/panel_command_handler.h"
#include "../game.h"

class Game;

class PanelState : public GameState {
public:
	PanelState(Game& g);
	void update(double delta) {}
	virtual void close();
	UIPanel& get_panel() const;

protected:
	Game& game;
	std::unique_ptr<UIPanel> panel;
};

#endif
