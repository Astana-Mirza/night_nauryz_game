#ifndef SFML_ENGINE_H
#define SFML_ENGINE_H

#include <vector>
#include <list>
#include <map>
#include <SFML/Graphics.hpp>
#include "../interfaces/render_engine.h"
#include "../field.h"
#include "../point2d.h"
#include "sfml_panel_view.h"
#include "sfml_panel_handler.h"
#include "resource_manager.h"

class SFMLEngine : public RenderEngine {
public:
	SFMLEngine(const std::shared_ptr<sf::RenderWindow>& win);
	void register_field(const Field& f);
	void register_cell(Point2D pos, const std::string& res);
	void register_cell_element(const CellElement& el,
				const std::string& res);
	std::unique_ptr<UIPanelView> register_panel(const std::string& texture);
	void pop_panel();
	void clear();
	void render_frame();
	void clear_preload_field();
	void apply_preload();

	void handle_move(const CellElement& el, Point2D pos);
	void handle_destruction(const CellElement& el);
	void handle_attack(const CellElement& el, int dmg,
					const CellElement& victim);
	void handle_charact_change(const CellElement& el,
			int prev, int curr, ActionListener::Characteristic c);
	void handle_pickup(const CellElement& el, bool is_picker);

private:
	void draw_field();
	void draw_cell_elements();
	void draw_panels();

	size_t w_width = 0, w_height = 0;		// window parameters
	size_t f_width = 0, f_height = 0;		// field parameters
	float cell_side;
	std::vector<sf::Sprite> tiles;
	std::map<size_t, sf::Sprite> objects;
	std::vector<sf::Sprite> preload_tiles;
	std::map<size_t, sf::Sprite> preload_objects;
	std::shared_ptr<sf::RenderWindow> window;
	std::list<SFMLPanelHandler> panels;
};

#endif
