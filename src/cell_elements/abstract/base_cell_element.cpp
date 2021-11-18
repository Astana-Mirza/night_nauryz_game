#include "../../../inc/cell_elements/abstract/base_cell_element.h"

BaseCellElement::BaseCellElement(IGameplayManager& gm, Point2D pos):
	gameplay{gm}, position{pos} {}

Point2D BaseCellElement::get_pos() const { return position; }

size_t BaseCellElement::get_id() const {
	return std::hash<const CellElement*>{}(this);
}

void BaseCellElement::destroy() {
	send_action(ActionDestroyed(*this));
	unsubscribe_all();
	gameplay.object_expired(gameplay.get_cell(position).get_element());
	gameplay.get_cell(position).remove_element();
}
