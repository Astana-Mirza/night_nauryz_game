#ifndef INFO_PANEL_H
#define INFO_PANEL_H

#include "../states/info_state.h"
#include "base_panel.h"
#include "menu_button.h"

class InfoState;

class InfoPanel : public BasePanel {
public:
	InfoPanel(RenderEngine& render, InfoState& st, const std::string& info);
	void notify(const std::string& event);

private:
	InfoState& state;
};

#endif
