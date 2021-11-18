#ifndef FINISH_CELL_H
#define FINISH_CELL_H

#include "cell.h"
#include "../interfaces/igameplay_manager.h"

class FinishCell : public Cell {
public:
	FinishCell(IGameplayManager& gm);
	void player_entered();
	std::unique_ptr<Cell> clone() const;

private:
	IGameplayManager& gameplay;
};

#endif
