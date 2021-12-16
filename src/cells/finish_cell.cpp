#include "../../inc/cells/finish_cell.h"

FinishCell::FinishCell(IGameplayManager& gm) :
		Cell::Cell(true), gameplay{gm} {}


void FinishCell::player_entered() {
	gameplay.level_completed();
}


std::unique_ptr<Cell> FinishCell::clone() const {
	auto cell_p = std::make_unique<FinishCell>(gameplay);
	if (element)
		cell_p->set_element(element->clone());
	return cell_p;
}

void FinishCell::accept(Visitor& vis) {
	vis.visit(*this);
}
