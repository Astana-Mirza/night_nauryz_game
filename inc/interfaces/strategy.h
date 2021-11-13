#ifndef STRATEGY_H
#define STRATEGY_H

#include "movable.h"

class Movable;

class Strategy {
public:
	virtual void execute(Movable& el) =0;
	virtual ~Strategy()=default;
};

#endif
