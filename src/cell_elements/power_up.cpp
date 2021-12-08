#include "../../inc/cell_elements/power_up.h"

void PowerUp::give_effect(Player& picker) {
	send_action(ActionPickedUp(*this, false));
	picker.change_power(characteristic);
	destroy();
}


void PowerUp::accept(Visitor& vis) {
	vis.visit(*this);
}


std::shared_ptr<CellElement> PowerUp::clone() const {
	return std::make_shared<PowerUp>(gameplay, characteristic, get_pos());
}
