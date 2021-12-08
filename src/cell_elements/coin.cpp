#include "../../inc/cell_elements/coin.h"

void Coin::give_effect(Player& picker) {
	send_action(ActionPickedUp(*this, false));
	gameplay.coin_picked();
	destroy();
}


std::shared_ptr<CellElement> Coin::clone() const {
	return std::make_shared<Coin>(gameplay, get_pos());
}


bool Coin::interact(Player& el) {
	give_effect(el);
	return true;
}


bool Coin::interact(CellElement& el) {
	return el.interact((PickupItem&)*this);
}

void Coin::accept(Visitor& vis) { vis.visit(*this); }
bool Coin::interact(Enemy& el) { return false; }
bool Coin::interact(PickupItem& el) { return false; }
