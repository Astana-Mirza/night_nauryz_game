#include "../../inc/ui/menu_button.h"

MenuButton::MenuButton(UIPanel& pan, const std::string& name):
	panel{pan}, button_name{name} {}

void MenuButton::click() {
	panel.notify(button_name);
}
