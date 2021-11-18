#include "../../../inc/cell_elements/abstract/base_pickup_item.h"

BasePickupItem::BasePickupItem(IGameplayManager& gm, int ch, Point2D p) :
	BaseCellElement::BaseCellElement(gm, p),
	characteristic{ch} {}


bool BasePickupItem::interact(Player& el) {
	give_effect(el);
	return true;
}


bool BasePickupItem::interact(CellElement& el) {
	return el.interact((PickupItem&)*this);
}

bool BasePickupItem::interact(Enemy& el) { return false; }

bool BasePickupItem::interact(PickupItem& el) { return false; }
