#include "../../inc/cells/start_cell.h"

StartCell::StartCell() : Cell::Cell(true) {}


std::unique_ptr<Cell> StartCell::clone() const {
	auto cell_p = std::make_unique<StartCell>();
	if (element)
		cell_p->set_element(element->clone());
	return cell_p;
}

