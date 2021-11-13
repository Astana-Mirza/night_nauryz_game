#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <string>
#include "interfaces/ui_panel.h"
#include "interfaces/ui_button.h"

class MenuButton : public UIButton {
public:
	MenuButton(UIPanel& pan, const std::string& name);
	void click();
private:
	UIPanel& panel;
	std::string button_name;
};

#endif
