#ifndef HEALER_H
#define HEALER_H

#include "abstract/base_pickup_item.h"

class Healer : public BasePickupItem {
public:
	using BasePickupItem::BasePickupItem;
	void give_effect(Player& picker);
	std::shared_ptr<CellElement> clone() const;
	void accept(Visitor& vis);
};

#endif
