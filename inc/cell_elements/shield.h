#ifndef SHIELD_H
#define SHIELD_H

#include "abstract/base_pickup_item.h"

class Shield :public BasePickupItem {
public:
	using BasePickupItem::BasePickupItem;
	void give_effect(Player& picker);
	std::shared_ptr<CellElement> clone() const;
};

#endif
