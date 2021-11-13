#include "../../inc/ui/base_panel.h"

void BasePanel::select_prev_button() {
	current_button = (buttons.size() + current_button - 1) % buttons.size();
	view->set_active_button(current_button);
}


void BasePanel::select_next_button() {
	current_button = (current_button + 1) % buttons.size();
	view->set_active_button(current_button);
}


void BasePanel::click_button() {
	buttons[current_button]->click();
}
