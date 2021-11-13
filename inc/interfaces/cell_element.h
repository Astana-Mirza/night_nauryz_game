#ifndef CELL_ELEMENT_H
#define CELL_ELEMENT_H

#include <memory>
#include "pickup_item.h"
#include "enemy.h"
#include "player.h"
#include "../point2d.h"

class CellElement {
public:
	virtual std::shared_ptr<CellElement> clone() const =0;
	virtual bool interact(CellElement& el) =0;
	virtual bool interact(PickupItem& el) =0;
	virtual bool interact(Enemy& el) =0;
	virtual bool interact(Player& el) =0;
	virtual void update() =0;
	virtual void destroy() =0;
	virtual size_t get_id() const =0;
	virtual Point2D get_pos() const =0;
	virtual ~CellElement() =default;
};

#endif
