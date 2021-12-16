#include "../../inc/ui/main_menu_panel.h"

#define PANEL_TEXTURE "res/ui/main_menu_panel.png"
#define MARKER_TEXTURE "res/ui/marker.png"
#define BTN_TEXTUTE "res/ui/button.png"
#define FONT "res/comic_sans_ru_en.ttf"

MainMenuPanel::MainMenuPanel(RenderEngine& render, MainMenuState& st):
							state{st} {
	view = render.register_panel(PANEL_TEXTURE);
	view->set_marker_texture(MARKER_TEXTURE);
	buttons.push_back(std::move(
			std::make_unique<MenuButton>(*this, "start")));
	view->add_button(633, 304, BTN_TEXTUTE, "Start game", FONT, 30);
	buttons.push_back(std::move(
			std::make_unique<MenuButton>(*this, "load")));
	view->add_button(633, 359, BTN_TEXTUTE, "Load game", FONT, 30);

	buttons.push_back(std::move(
			std::make_unique<MenuButton>(*this, "difficulty")));
	view->add_button(633, 414, BTN_TEXTUTE, "Difficulty: Easy", FONT, 30);

	buttons.push_back(std::move(
			std::make_unique<MenuButton>(*this, "quit")));
	view->add_button(633, 469, BTN_TEXTUTE, "Quit", FONT, 30);

	view->set_active_button(0);
}


void MainMenuPanel::notify(const std::string& event) {
	if (event == "start")
		state.start_game();
	else if (event == "load")
		state.load_game();
	else if (event == "difficulty") {
		curr_diff = (curr_diff+1) % difficulties.size();
		view->set_button_label(
			2, "Difficulty: " + difficulties[curr_diff], FONT, 30);
		state.set_difficulty(difficulties[curr_diff]);
	}
	else if (event == "quit")
		state.close();
}
