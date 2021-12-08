#include "../../inc/cells/cell.h"


Cell::Cell(bool pass) : passable{pass}, element{nullptr} {}


std::unique_ptr<Cell> Cell::clone() const {
	auto cell_p = std::make_unique<Cell>(passable);
	if (element)
		cell_p->set_element(element->clone());
	return cell_p;
}


void Cell::set_element(const std::shared_ptr<CellElement>& el) {
	element = el;
}

void Cell::accept(Visitor& vis) { vis.visit(*this); }
void Cell::remove_element() { element = nullptr; }
bool Cell::empty() const { return element==nullptr; }
bool Cell::is_passable() const { return passable; }
const std::shared_ptr<CellElement>& Cell::get_element() const { return element; }
