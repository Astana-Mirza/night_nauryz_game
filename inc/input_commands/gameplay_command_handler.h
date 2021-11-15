#ifndef GAMEPLAY_COMMAND_HANDLER_H
#define GAMEPLAY_COMMAND_HANDLER_H

#include "../interfaces/igameplay_manager.h"
#include "base_command_handler.h"


class GameplayCommandHandler : public BaseCommandHandler {
public:
	GameplayCommandHandler(IGameplayManager& gp);
	void handle_command(InputCommand c);

private:
	IGameplayManager& gameplay;
};

#endif
