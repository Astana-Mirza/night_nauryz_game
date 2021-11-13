#ifndef GAMEPLAY_COMMAND_HANDLER_H
#define GAMEPLAY_COMMAND_HANDLER_H

#include "../states/gameplay_state.h"
#include "base_command_handler.h"

class GameplayState;

class GameplayCommandHandler : public BaseCommandHandler {
public:
	GameplayCommandHandler(GameplayState& gp);
	void handle_command(InputCommand c);

private:
	GameplayState& gameplay;
};

#endif
