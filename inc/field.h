#ifndef FIELD_H
#define FIELD_H

#include <memory>
#include <stdexcept>
#include "cells/cell.h"
#include "point2d.h"

class Cell;

class Field {
public:
	Field(size_t width, size_t height);
	Field(const Field& w);			// copy
	Field(Field&& w);			// move
	Field& operator =(const Field& w);	// copy assign
	Field& operator =(Field&& w);		// move assign

	void set_cell(Point2D pos, std::unique_ptr<Cell>&& cell);
	Cell& get_cell(Point2D pos) const;

	size_t get_width() const;
	size_t get_height() const;

	class iterator {
	private:
		const Field& field;
		Point2D pos;
	public:
		explicit iterator(const Field& f, Point2D p={0, 0});
		iterator& operator++();
		iterator operator++(int);
		bool operator==(iterator other) const;
		bool operator!=(iterator other) const;
		Cell& operator*() const;
	};

	iterator begin();
	iterator end();

private:
	using cell_ptr = std::unique_ptr<Cell>;
	using cell_ptr_arr = std::unique_ptr<cell_ptr[]>;

	size_t cell_width, cell_height;
	std::unique_ptr<cell_ptr_arr[]> cells;
	std::unique_ptr<Cell> wall_cell = std::make_unique<Cell>(false);
};

#endif

