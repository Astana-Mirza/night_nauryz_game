#ifndef CELL_H
#define CELL_H

#include <memory>
#include <set>
#include <iostream>
#include "../interfaces/cell_element.h"
#include "../interfaces/visitor.h"

class Visitor;

class Cell {
public:
	Cell(bool pass=true);
	virtual ~Cell() =default;
	virtual std::unique_ptr<Cell> clone() const;
	//virtual void player_acted() {}
	//virtual void player_exited() {}
	virtual void accept(Visitor& vis);
	virtual void player_entered() {}
	void set_element(const std::shared_ptr<CellElement>& el);
	void remove_element();
	bool empty() const;
	bool is_passable() const;
	const std::shared_ptr<CellElement>& get_element() const;

protected:
	bool passable;
	std::shared_ptr<CellElement> element;
};

#endif
