#ifndef COIN_H
#define COIN_H

#include "abstract/base_cell_element.h"
#include "../actions/action_picked_up.h"
#include "../interfaces/pickup_item.h"

class Coin : public BaseCellElement, public PickupItem {
public:
	using BaseCellElement::BaseCellElement;
	void give_effect(Player& picker);
	std::shared_ptr<CellElement> clone() const;
	void accept(Visitor& vis);
	bool interact(CellElement& el);
	bool interact(Enemy& el);
	bool interact(PickupItem& el);
	bool interact(Player& el);
};

#endif
