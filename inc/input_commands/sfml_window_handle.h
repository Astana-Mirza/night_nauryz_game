#ifndef SFML_WINDOW_HANDLE_H
#define SFML_WINDOW_HANDLE_H

#include <map>
#include <SFML/Graphics.hpp>
#include "../interfaces/window_handle.h"
#include "../utility/config_manager.h"

class SFMLWindowHandle : public WindowHandle {
public:
	SFMLWindowHandle(const std::shared_ptr<sf::RenderWindow>& win);
	void process_commands();
	void set_command_handler(
			const std::shared_ptr<CommandHandler>& handler);

private:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<CommandHandler> command_handler;
};

#endif
