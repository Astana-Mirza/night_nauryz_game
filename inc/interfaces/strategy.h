#ifndef STRATEGY_H
#define STRATEGY_H

#include "visitor.h"
#include "movable.h"

class Visitor;
class Movable;

class Strategy {
public:
	virtual void accept(Visitor& vis) =0;
	virtual void execute(Movable& el) =0;
	virtual bool get_direction() const =0;
	virtual ~Strategy()=default;
};

#endif
