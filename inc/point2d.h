#ifndef POINT2D_H
#define POINT2D_H


struct Point2D {
	int x = 0;
	int y = 0;
	bool operator== (const Point2D& p) const;
	bool operator!= (const Point2D& p) const;
	Point2D& operator+= (const Point2D& p);
	Point2D& operator-= (const Point2D& p);
};

Point2D operator+ (const Point2D& pl, const Point2D& pr);
Point2D operator- (const Point2D& pl, const Point2D& pr);

#endif

