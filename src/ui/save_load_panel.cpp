#include "../../inc/ui/save_load_panel.h"

#define PANEL_TEXTURE "res/ui/pause_panel.png"
#define MARKER_TEXTURE "res/ui/marker.png"
#define BTN_TEXTUTE "res/ui/button.png"
#define FONT "res/comic_sans_ru_en.ttf"

SaveLoadPanel::SaveLoadPanel(RenderEngine& render, SaveLoadState& st):
							state{st} {
	view = render.register_panel(PANEL_TEXTURE);
	view->set_marker_texture(MARKER_TEXTURE);

	buttons.push_back(std::move(
			std::make_unique<MenuButton>(*this, "cancel")));
	view->add_button(50, 100, BTN_TEXTUTE, "Cancel", FONT, 30);
	buttons.push_back(std::move(
			std::make_unique<MenuButton>(*this, "slot1")));
	view->add_button(50, 175, BTN_TEXTUTE, "Slot 1", FONT, 30);
	buttons.push_back(std::move(
			std::make_unique<MenuButton>(*this, "slot2")));
	view->add_button(50, 250, BTN_TEXTUTE, "Slot 2", FONT, 30);
	buttons.push_back(std::move(
			std::make_unique<MenuButton>(*this, "slot3")));
	view->add_button(50, 325, BTN_TEXTUTE, "Slot 3", FONT, 30);
	view->set_active_button(0);
}


void SaveLoadPanel::notify(const std::string& event) {
	if (event == "cancel")
		state.close();
	else
		state.save_or_load(event.back()-'0');
}
