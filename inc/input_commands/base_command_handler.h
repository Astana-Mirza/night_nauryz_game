#ifndef BASE_COMMAND_HANDLER_H
#define BASE_COMMAND_HANDLER_H

#include <memory>
#include "../interfaces/command_handler.h"

class BaseCommandHandler : public CommandHandler {
public:
	void set_next(const std::shared_ptr<CommandHandler>& n) { next = n; }
protected:
	std::shared_ptr<CommandHandler> next;
};

#endif
