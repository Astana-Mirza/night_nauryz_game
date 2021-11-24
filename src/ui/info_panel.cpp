#include "../../inc/ui/info_panel.h"

#define PANEL_TEXTURE "res/ui/pause_panel.png"
#define MARKER_TEXTURE "res/ui/marker.png"
#define BTN_TEXTUTE "res/ui/button.png"
#define FONT "res/comic_sans_ru_en.ttf"

InfoPanel::InfoPanel(RenderEngine& render, InfoState& st,
				const std::string& info) : state{st} {
	view = render.register_panel(PANEL_TEXTURE);
	view->set_marker_texture(MARKER_TEXTURE);

	view->add_label(0, 0, info, FONT, 30);
	buttons.push_back(std::move(
			std::make_unique<MenuButton>(*this, "ok")));
	view->add_button(50, 100, BTN_TEXTUTE, "OK", FONT, 30);
	view->set_active_button(0);
}


void InfoPanel::notify(const std::string& event) {
	if (event == "ok")
		state.close();
}
