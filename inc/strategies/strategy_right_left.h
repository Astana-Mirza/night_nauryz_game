#ifndef STRATEGY_RIGHT_LEFT_H
#define STRATEGY_RIGHT_LEFT_H

#include "../interfaces/strategy.h"
#include "../point2d.h"

class StrategyRightLeft : public Strategy {
public:
	StrategyRightLeft(bool r=true);
	void execute(Movable& el);

private:
	bool right;
};

#endif

