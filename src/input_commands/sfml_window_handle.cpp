#include "../../inc/input_commands/sfml_window_handle.h"

SFMLWindowHandle::SFMLWindowHandle(const std::shared_ptr<sf::RenderWindow>& win):
	window{win} {}


void SFMLWindowHandle::process_commands() {
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type != sf::Event::KeyPressed)
			continue;
		auto command = ConfigManager::instance()
					.key_to_command(event.key.code);
		if (command_handler)
			command_handler->handle_command(command);
	}
}


void SFMLWindowHandle::set_command_handler(
		const std::shared_ptr<CommandHandler>& handler) {
	command_handler = handler;
}
