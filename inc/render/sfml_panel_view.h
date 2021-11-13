#ifndef SFML_PANEL_VIEW_H
#define SFML_PANEL_VIEW_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "../interfaces/ui_panel_view.h"
#include "sfml_button_handler.h"
#include "resource_manager.h"

class SFMLPanelView : public UIPanelView {
public:
	SFMLPanelView(const sf::Sprite& pan, sf::Sprite& marker,
			std::vector<sf::Text>& lbls,
			std::vector<SFMLButtonHandler>& btns);
	void set_marker_texture(const std::string& texture);
	void add_button(float x, float y, const std::string& texture,
		const std::string& text, const std::string& font, size_t charsize);
	void set_button_label(size_t btn_num, const std::string& text,
				const std::string& font, size_t charsize);
	void add_label(float x, float y, const std::string& text,
				const std::string& font, size_t charsize);
	void set_active_button(size_t btn_num);

private:
	const sf::Sprite& panel_sprite;
	sf::Sprite& marker_sprite;
	std::vector<sf::Text>& labels;
	std::vector<SFMLButtonHandler>& buttons;
};

#endif
