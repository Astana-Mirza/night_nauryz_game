#ifndef PANEL_COMMAND_HANDLER_H
#define PANEL_COMMAND_HANDLER_H

#include "../states/panel_state.h"
#include "base_command_handler.h"

class PanelState;

class PanelCommandHandler : public BaseCommandHandler {
public:
	PanelCommandHandler(PanelState& pstate);
	void handle_command(InputCommand c);

private:
	PanelState& state;
};

#endif
