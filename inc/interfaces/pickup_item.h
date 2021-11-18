#ifndef PICKUP_ITEM_H
#define PICKUP_ITEM_H

#include "player.h"

class Player;

class PickupItem {
public:
	virtual void give_effect(Player& picker) =0;
	virtual ~PickupItem() =default;
};

#endif
