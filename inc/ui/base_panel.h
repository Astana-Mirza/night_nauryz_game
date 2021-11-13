#ifndef BASE_PANEL_H
#define BASE_PANEL_H

#include <memory>
#include <vector>
#include "../interfaces/ui_panel.h"
#include "../interfaces/ui_panel_view.h"

class BasePanel : public UIPanel {
public:
	void select_prev_button();
	void select_next_button();
	void click_button();

protected:
	std::vector<std::unique_ptr<UIButton>> buttons;
	std::unique_ptr<UIPanelView> view;

private:
	size_t current_button = 0;
};

#endif
