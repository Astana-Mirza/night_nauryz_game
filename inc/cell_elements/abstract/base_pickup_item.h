#ifndef BASE_PICKUP_ITEM_H
#define BASE_PICKUP_ITEM_H

#include "base_cell_element.h"
#include "../../actions/action_picked_up.h"
#include "../../interfaces/pickup_item.h"

class BasePickupItem : public BaseCellElement,
			public PickupItem {
public:
	BasePickupItem(IGameplayManager& gm, int ch, Point2D p);
	int get_characteristic() const;
	bool interact(CellElement& el);
	bool interact(Enemy& el);
	bool interact(PickupItem& el);
	bool interact(Player& el);

protected:
	int characteristic;
};

#endif
