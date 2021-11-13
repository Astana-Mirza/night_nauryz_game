#ifndef SFML_PANEL_HANDLER_H
#define SFML_PANEL_HANDLER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "sfml_button_handler.h"

struct SFMLPanelHandler {
	sf::Sprite panel_sprite;
	sf::Sprite marker_sprite;
	std::vector<sf::Text> labels;
	std::vector<SFMLButtonHandler> buttons;
};

#endif
