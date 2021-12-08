#include "../../inc/render/sfml_engine.h"

SFMLEngine::SFMLEngine(const std::shared_ptr<sf::RenderWindow>& win):
							window{win} {
	w_width = window->getSize().x;
	w_height = window->getSize().y;
}


void SFMLEngine::register_field(const Field& f) {
	f_width = f.get_width();
	f_height = f.get_height();
	cell_side = std::min(static_cast<float>(w_height) / f_height,
				static_cast<float>(w_width) / f_width);
	size_t offset_x = (w_width - f_width*cell_side)/2;
	size_t offset_y = (w_height - f_height*cell_side)/2;
	preload_tiles = std::vector<sf::Sprite>(f_width*f_height);
	for (size_t i = 0; i < f_width; i++) {
		for (size_t j = 0; j < f_height; j++) {
			preload_tiles[j*f_width+i].setPosition(offset_x + i*cell_side,
							offset_y + j*cell_side);
		}
	}
}


void SFMLEngine::register_cell(Point2D pos, const std::string& res) {
	const auto& t = ResourceManager<sf::Texture>::instance().get(res);
	preload_tiles[pos.y*f_width+pos.x].setTexture(t);
	preload_tiles[pos.y*f_width+pos.x].setScale(
		cell_side/t.getSize().x,
		cell_side/t.getSize().y);
}


void SFMLEngine::register_cell_element(const CellElement& el,
					const std::string& res) {
	const auto& t = ResourceManager<sf::Texture>::instance().get(res);
	auto pos = el.get_pos();
	sf::Sprite sp(t);
	sp.setPosition(preload_tiles[pos.y*f_width+pos.x].getPosition());
	sp.setScale( cell_side/t.getSize().x, cell_side/t.getSize().y );
	preload_objects[el.get_id()] = sp;
}


std::unique_ptr<UIPanelView> SFMLEngine::register_panel(
					const std::string& texture) {
	sf::Sprite pan(ResourceManager<sf::Texture>::instance().get(texture));
	auto bounds = pan.getLocalBounds();
	pan.setPosition((w_width-bounds.width)/2, (w_height-bounds.height)/2);
	panels.push_back(SFMLPanelHandler{});
	auto& handler = panels.back();
	handler.panel_sprite = pan;
	auto view = std::make_unique<SFMLPanelView>(handler.panel_sprite,
		handler.marker_sprite, handler.labels, handler.buttons);
	return std::move(view);
}


void SFMLEngine::pop_panel() {
	panels.pop_back();
}


void SFMLEngine::clear_preload_field() {
	preload_tiles = {};
	preload_objects = {};
}


void SFMLEngine::apply_preload() {
	tiles = std::move(preload_tiles);
	objects = std::move(preload_objects);
}


void SFMLEngine::clear() {
	tiles = {};
	objects = {};
	panels = {};
}

void SFMLEngine::render_frame() {
	window->clear();
	draw_field();
	draw_cell_elements();
	draw_panels();
	window->display();
}


void SFMLEngine::draw_field() {
	for (auto& t : tiles) {
		window->draw(t);
	}
}


void SFMLEngine::draw_cell_elements() {
	for (auto& [key, val] : objects) {
		window->draw(val);
	}
}


void SFMLEngine::draw_panels() {
	for (const auto& handler : panels) {
		window->draw(handler.panel_sprite);
		for (const auto& lab : handler.labels) {
			window->draw(lab);
		}
		for (const auto& btn : handler.buttons) {
			window->draw(btn.sprite);
			window->draw(btn.label);
		}
		window->draw(handler.marker_sprite);
	}
}


void SFMLEngine::handle_destruction(const CellElement& el) {
	objects.erase(el.get_id());
}


void SFMLEngine::handle_move(const CellElement& el, Point2D pos) {
	objects[el.get_id()].setPosition(
		tiles[pos.y*f_width+pos.x].getPosition()
	);
}


void SFMLEngine::handle_attack(const CellElement& el, int dmg,
				const CellElement& victim) {}


void SFMLEngine::handle_charact_change(const CellElement& el,
		int prev, int curr, ActionListener::Characteristic c) {}


void SFMLEngine::handle_pickup(const CellElement& el, bool is_picker) {}
