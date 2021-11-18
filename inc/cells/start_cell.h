#ifndef START_CELL_H
#define START_CELL_H

#include "cell.h"

class StartCell : public Cell {
public:
	StartCell();
	std::unique_ptr<Cell> clone() const;
};

#endif

