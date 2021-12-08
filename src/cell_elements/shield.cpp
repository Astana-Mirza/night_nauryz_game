#include "../../inc/cell_elements/shield.h"

void Shield::give_effect(Player& picker) {
	send_action(ActionPickedUp(*this, false));
	picker.change_armor(characteristic);
	destroy();
}


void Shield::accept(Visitor& vis) {
	vis.visit(*this);
}


std::shared_ptr<CellElement> Shield::clone() const {
	return std::make_shared<Shield>(gameplay, characteristic, get_pos());
}
