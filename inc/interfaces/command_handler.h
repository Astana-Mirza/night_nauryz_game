#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <memory>

enum class InputCommand {
	Unknown,
	MoveRight,
	MoveLeft,
	MoveUp,
	MoveDown,
	DoAction,
	Back
};

class CommandHandler {
public:
	virtual void handle_command(InputCommand c) =0;
	virtual void set_next(const std::shared_ptr<CommandHandler>& n) =0;
	virtual ~CommandHandler() =default;
};

#endif
