#ifndef STRATEGY_UP_DOWN_H
#define STRATEGY_UP_DOWN_H

#include "../interfaces/strategy.h"
#include "../point2d.h"

class StrategyUpDown : public Strategy {
public:
	StrategyUpDown(bool d=true);
	bool get_direction() const;
	void execute(Movable& el);
	void accept(Visitor& vis);

private:
	bool down;
};

#endif
