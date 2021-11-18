#ifndef PLAYER_COMMAND_HANDLER_H
#define PLAYER_COMMAND_HANDLER_H

#include "base_command_handler.h"
#include "../interfaces/player.h"

class PlayerCommandHandler: public BaseCommandHandler {
public:
	PlayerCommandHandler(Player& p);
	void handle_command(InputCommand c);

private:
	Player& player;
};

#endif
