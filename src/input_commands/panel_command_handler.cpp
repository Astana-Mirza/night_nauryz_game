#include "../../inc/input_commands/panel_command_handler.h"

PanelCommandHandler::PanelCommandHandler(PanelState& pstate) : state{pstate} {}

void PanelCommandHandler::handle_command(InputCommand c) {
	switch (c) {
		case InputCommand::Back:
			state.close();
		break;
		case InputCommand::DoAction:
			state.get_panel().click_button();
		break;
		case InputCommand::MoveUp:
			state.get_panel().select_prev_button();
		break;
		case InputCommand::MoveDown:
			state.get_panel().select_next_button();
		break;
		default:
			if (next)
				next->handle_command(c);
		break;
	}
}
