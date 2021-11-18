#include "../../inc/logger/stream_operators.h"

std::ostream& operator<<(std::ostream& os, const CellElement& el) {
	os << "CellElement" << el.get_pos();
	return os;
}

/*std::ostream& operator<<(std::ostream& os, const Attackable& el) {
	os << "Attackable[" << std::hex << &el << std::dec << ']';
	return os;
}*/

std::ostream& operator<<(std::ostream& os, const Point2D& p) {
	os << '(' << p.x << ", " << p.y << ')';
	return os;
}
