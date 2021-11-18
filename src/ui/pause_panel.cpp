#include "../../inc/ui/pause_panel.h"

#define PANEL_TEXTURE "res/ui/pause_panel.png"
#define MARKER_TEXTURE "res/ui/marker.png"
#define BTN_TEXTUTE "res/ui/button.png"
#define FONT "res/comic_sans_ru_en.ttf"

PausePanel::PausePanel(RenderEngine& render, PauseState& st) : state{st} {
	view = render.register_panel(PANEL_TEXTURE);
	view->set_marker_texture(MARKER_TEXTURE);

	buttons.push_back(std::move(
			std::make_unique<MenuButton>(*this, "resume")));
	view->add_button(50, 100, BTN_TEXTUTE, "Resume", FONT, 30);

	buttons.push_back(std::move(
			std::make_unique<MenuButton>(*this, "quit")));
	view->add_button(50, 175, BTN_TEXTUTE, "Quit", FONT, 30);

	view->set_active_button(0);
}


void PausePanel::notify(const std::string& event) {
	if (event == "resume")
		state.close();
	else if (event == "quit")
		state.quit();
}
