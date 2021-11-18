#include "../../inc/input_commands/gameplay_command_handler.h"

GameplayCommandHandler::GameplayCommandHandler(IGameplayManager& gp):
	gameplay{gp} {}


void GameplayCommandHandler::handle_command(InputCommand c) {
	if (c == InputCommand::Back) {
		gameplay.game_paused();
	} else if (next) {
		next->handle_command(c);
	}
	// pass other commands to player
}
