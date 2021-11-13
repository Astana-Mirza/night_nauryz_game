#ifndef STREAM_OPERATORS_H
#define STREAM_OPERATORS_H

#include "../interfaces/cell_element.h"
#include "../interfaces/attackable.h"
#include "../point2d.h"
#include <ostream>

std::ostream& operator<<(std::ostream& os, const CellElement& el);
//std::ostream& operator<<(std::ostream& os, const Attackable& el);
std::ostream& operator<<(std::ostream& os, const Point2D& p);

#endif
