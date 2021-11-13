#ifndef WINDOW_HANDLE_H
#define WINDOW_HANDLE_H

#include "command_handler.h"

class WindowHandle {
public:
	virtual void process_commands() =0;
	virtual void set_command_handler(
			const std::shared_ptr<CommandHandler>& n) =0;
	virtual ~WindowHandle() =default;
};

#endif
