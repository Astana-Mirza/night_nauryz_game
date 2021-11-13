#ifndef PLAYER_H
#define PLAYER_H

#include "../point2d.h"
#include "command_handler.h"
#include "attackable.h"
#include "pickup_item.h"

class PickupItem;

class Player : public virtual Attackable {
public:
	virtual void pickup(PickupItem& it) =0;
	virtual void set_move_dest(Point2D pos) =0;
	virtual std::shared_ptr<CommandHandler> get_command_handler() const =0;
};

#endif
