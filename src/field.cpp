#include "field.h"

Field::Field(size_t width, size_t height)
			: cell_width{width}, cell_height{height} {
	cells = std::make_unique<cell_ptr_arr[]>(cell_width);
	for (size_t i = 0; i < cell_width; i++) {
		cells[i] = std::make_unique<cell_ptr[]>(cell_height);
	}
}


Field::Field(const Field& w) : Field::Field(w.cell_width, w.cell_height) {
	for (int i = 0; (size_t)i < cell_width; i++) {
		for (int j = 0; (size_t)j < cell_height; j++) {
			cells[i][j] = std::move(w.get_cell({i, j}).clone());
		}
	}
}


Field::Field(Field&& w) {
	std::swap(cell_width, w.cell_width);
	std::swap(cell_height, w.cell_height);
	std::swap(cells, w.cells);
}


Field& Field::operator =(const Field& w) {
	if (&w != this) {
		cell_width = w.cell_width;
		cell_height = w.cell_height;
		cells = std::make_unique<cell_ptr_arr[]>(cell_width);
		for (int i = 0; (size_t)i < cell_width; i++) {
			cells[i] = std::make_unique<cell_ptr[]>(cell_height);
			for (int j = 0; (size_t)j < cell_height; j++) {
				cells[i][j] = std::move(w.get_cell({i, j}).clone());
			}
		}
	}
	return *this;
}


Field& Field::operator =(Field&& w) {
	if (&w != this) {
		cells = nullptr;
		std::swap(cell_width, w.cell_width);
		std::swap(cell_height, w.cell_height);
		std::swap(cells, w.cells);
	}
	return *this;
}


void Field::set_cell(Point2D pos, std::unique_ptr<Cell>&& cell) {
	if (pos.x < 0  || (size_t)pos.x >= cell_width ||
			pos.y < 0 || (size_t)pos.y >= cell_height)
		throw std::runtime_error{"Wrong cell position"};
	cells[pos.x][pos.y] = std::move(cell);
}


Cell& Field::get_cell(Point2D pos) const {
	if (pos.x >= 0 && (size_t)pos.x < cell_width &&
			pos.y >= 0 && (size_t)pos.y < cell_height)
		return *cells[pos.x][pos.y];
	return *wall_cell;
}

size_t Field::get_width() const { return cell_width; }

size_t Field::get_height() const { return cell_height; }


Field::iterator::iterator(const Field& f, Point2D p) :
	field{f}, pos{p} {}


Field::iterator& Field::iterator::operator++() {
	++pos.x;
	if ((size_t)pos.x >= field.get_width()) {
		++pos.y;
		pos.x = 0;
	}
	return *this;
}


Field::iterator Field::iterator::operator++(int) {
	Field::iterator retval = *this;
	++(*this);
	return retval;
}


bool Field::iterator::operator==(iterator other) const {
	return pos == other.pos;
}


bool Field::iterator::operator!=(iterator other) const {
	return !(*this == other);
}

Cell& Field::iterator::operator*() const { return field.get_cell(pos); }

Field::iterator Field::begin() { return Field::iterator(*this); }

Field::iterator Field::end() {
	return Field::iterator(*this, {0, (int)get_height()});
}

