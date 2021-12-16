#ifndef POWER_UP_H
#define POWER_UP_H

#include "abstract/base_pickup_item.h"

class PowerUp :public BasePickupItem {
public:
	using BasePickupItem::BasePickupItem;
	void give_effect(Player& picker);
	std::shared_ptr<CellElement> clone() const;
	void accept(Visitor& vis);
};

#endif
