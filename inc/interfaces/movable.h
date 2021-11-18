#ifndef MOVABLE_H
#define MOVABLE_H

#include "../point2d.h"

class Movable {
public:
	virtual bool move_to(Point2D r) =0;
	virtual bool move(Point2D dr) =0;
	virtual ~Movable() =default;
};

#endif
