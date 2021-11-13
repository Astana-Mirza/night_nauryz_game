#ifndef STRATEGY_UP_DOWN_H
#define STRATEGY_UP_DOWN_H

#include "../interfaces/strategy.h"
#include "../point2d.h"

class StrategyUpDown : public Strategy {
public:
	StrategyUpDown(bool d=true);
	void execute(Movable& el);

private:
	bool down;
};

#endif

