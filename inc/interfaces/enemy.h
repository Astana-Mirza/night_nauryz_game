#ifndef ENEMY_H
#define ENEMY_H

#include <memory>
#include "attackable.h"
#include "strategy.h"

class Enemy : public virtual Attackable {
public:
	virtual void set_strategy(std::unique_ptr<Strategy>&& s) =0;
};

#endif

