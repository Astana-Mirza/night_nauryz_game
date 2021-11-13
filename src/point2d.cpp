#include "../inc/point2d.h"

bool Point2D::operator== (const Point2D& p) const {
	return (x == p.x) && (y == p.y);
}


bool Point2D::operator!= (const Point2D& p) const {
	return !(*this == p);
}


Point2D& Point2D::operator+= (const Point2D& p) {
	x += p.x;
	y += p.y;
	return *this;
}


Point2D& Point2D::operator-= (const Point2D& p) {
	x += p.x;
	y += p.y;
	return *this;
}


Point2D operator+ (const Point2D& pl, const Point2D& pr) {
	return Point2D{pl.x + pr.x, pl.y + pr.y};
}


Point2D operator- (const Point2D& pl, const Point2D& pr) {
	return Point2D{pl.x - pr.x, pl.y - pr.y};
}

