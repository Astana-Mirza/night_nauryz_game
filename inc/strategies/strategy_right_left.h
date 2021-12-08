#ifndef STRATEGY_RIGHT_LEFT_H
#define STRATEGY_RIGHT_LEFT_H

#include "../interfaces/strategy.h"
#include "../point2d.h"

class StrategyRightLeft : public Strategy {
public:
	StrategyRightLeft(bool r=true);
	bool get_direction() const;
	void execute(Movable& el);
	void accept(Visitor& vis);

private:
	bool right;
};

#endif
