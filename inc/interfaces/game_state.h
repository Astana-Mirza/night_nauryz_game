#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "command_handler.h"

class GameState {
public:
	virtual void update(double delta) =0;
	std::shared_ptr<CommandHandler> get_command_handler() const {
		return command_handler;
	}
	virtual ~GameState() =default;

protected:
	std::shared_ptr<CommandHandler> command_handler;
};

#endif
