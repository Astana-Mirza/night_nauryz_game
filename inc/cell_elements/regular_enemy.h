#ifndef REGULAR_ENEMY_H
#define REGULAR_ENEMY_H

#include "../interfaces/enemy.h"
#include "abstract/attackable_element.h"

class RegularEnemy : public AttackableElement, public Enemy {
public:
	using AttackableElement::AttackableElement;
	std::shared_ptr<CellElement> clone() const;
	void update();
	void set_strategy(std::unique_ptr<Strategy>&& s);
	bool interact(CellElement& el);
	bool interact(Enemy& el);
	bool interact(PickupItem& el);
	bool interact(Player& el);

private:
	std::unique_ptr<Strategy> strategy;
};

#endif
