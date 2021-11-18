#include "../../inc/input_commands/player_command_handler.h"

PlayerCommandHandler::PlayerCommandHandler(Player& p) : player{p} {}

void PlayerCommandHandler::handle_command(InputCommand c) {
	switch (c) {
		case InputCommand::MoveRight:
			player.set_move_dest({1, 0});
		break;
		case InputCommand::MoveLeft:
			player.set_move_dest({-1, 0});
		break;
		case InputCommand::MoveUp:
			player.set_move_dest({0, -1});
		break;
		case InputCommand::MoveDown:
			player.set_move_dest({0, 1});
		break;
		case InputCommand::DoAction:
			// player action code
		break;
		default:
			if (next)
				next->handle_command(c);
		break;
	}
}
