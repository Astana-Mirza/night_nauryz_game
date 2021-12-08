#ifndef START_CELL_H
#define START_CELL_H

#include "cell.h"

class Visitor;

class StartCell : public Cell {
public:
	StartCell();
	void accept(Visitor& vis);
	std::unique_ptr<Cell> clone() const;
};

#endif
