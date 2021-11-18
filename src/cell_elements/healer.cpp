#include "../../inc/cell_elements/healer.h"

void Healer::give_effect(Player& picker) {
	send_action(ActionPickedUp(*this, false));
	picker.change_hp(characteristic);
	destroy();
}


std::shared_ptr<CellElement> Healer::clone() const {
	return std::make_shared<Healer>(gameplay, characteristic, get_pos());
}
