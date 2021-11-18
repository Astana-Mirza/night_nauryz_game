#ifndef MOVABLE_ELEMENT_H
#define MOVABLE_ELEMENT_H

#include "../../interfaces/movable.h"
#include "../../actions/action_moved.h"
#include "base_cell_element.h"

class MovableElement : public BaseCellElement, public Movable {
public:
	using BaseCellElement::BaseCellElement;
	bool move_to(Point2D r);
	bool move(Point2D dr);
};

#endif

