#include "../../inc/render/sfml_panel_view.h"

SFMLPanelView::SFMLPanelView(const sf::Sprite& pan, sf::Sprite& marker,
		std::vector<sf::Text>& lbls,
		std::vector<SFMLButtonHandler>& btns) : panel_sprite{pan},
		marker_sprite{marker}, labels{lbls}, buttons{btns} {}


void SFMLPanelView::set_marker_texture(const std::string& texture) {
	marker_sprite.setTexture(
		ResourceManager<sf::Texture>::instance().get(texture));
}


void SFMLPanelView::add_button(float x, float y, const std::string& texture,
			const std::string& text, const std::string& font,
							size_t charsize) {
	sf::Sprite btn_sprite(
		ResourceManager<sf::Texture>::instance().get(texture));
	auto panel_pos = panel_sprite.getPosition();
	btn_sprite.setPosition(panel_pos.x + x, panel_pos.y + y);
	const auto& f = ResourceManager<sf::Font>::instance().get(font);
	sf::Text label(text, f, charsize);
	label.setStyle(sf::Text::Bold);
	label.setFillColor(sf::Color::White);
	//auto sprite_pos = btn_sprite.getPosition();
	//auto bounds = label.getLocalBounds();
	//label.setPosition((sprite_pos.x-bounds.width)/2,
	//			(sprite_pos.y-bounds.height)/2);
	label.setPosition(btn_sprite.getPosition());
	buttons.push_back({btn_sprite, label});
}


void SFMLPanelView::set_button_label(size_t btn_num, const std::string& text,
			const std::string& font, size_t charsize) {
	auto& label = buttons.at(btn_num).label;
	label.setString(text);
	label.setFont(ResourceManager<sf::Font>::instance().get(font));
	label.setCharacterSize(charsize);
}


void SFMLPanelView::add_label(float x, float y, const std::string& text,
				const std::string& font, size_t charsize) {
	const auto& f = ResourceManager<sf::Font>::instance().get(font);
	sf::Text label(text, f, charsize);
	auto panel_pos = panel_sprite.getPosition();
	label.setPosition(panel_pos.x + x, panel_pos.y + y);
	label.setStyle(sf::Text::Bold);
	label.setFillColor(sf::Color::White);
	labels.push_back(label);
}


void SFMLPanelView::set_active_button(size_t btn_num) {
	auto pos = buttons.at(btn_num).sprite.getPosition();
	marker_sprite.setPosition(pos);
}
