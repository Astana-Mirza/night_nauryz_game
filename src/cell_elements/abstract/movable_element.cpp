#include "../../../inc/cell_elements/abstract/movable_element.h"

bool MovableElement::move_to(Point2D r) {
	auto& c = gameplay.get_cell(r);
	if (r == position) {
		return true;
	}
	if (!c.is_passable()) {
		return false;
	}
	if (!c.empty()) {
		if (!c.get_element()->interact(*this)) {
			return false;
		}
	}
	if (c.empty()) { // check again if we freed the cell
		auto& current = gameplay.get_cell(position);
		send_action(ActionMoved(*this, r));
		c.set_element(current.get_element());
		current.remove_element();
		position = r;
	}
	return true;
}

bool MovableElement::move(Point2D dr) {
	return move_to(position + dr);
}
