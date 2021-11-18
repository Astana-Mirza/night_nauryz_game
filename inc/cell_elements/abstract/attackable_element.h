#ifndef ATTACKABLE_ELEMENT_H
#define ATTACKABLE_ELEMENT_H

#include "../../interfaces/attackable.h"
#include "../../actions/action_attacked.h"
#include "../../actions/action_charact_changed.h"
#include "movable_element.h"

class AttackableElement : public MovableElement,
			public virtual Attackable {
public:
	AttackableElement(IGameplayManager& gm, int hp, int arm,
						int pwr, Point2D p);
	int calculate_damage(int power) const;
	int change_hp(int hp);
	int change_armor(int arm);
	int change_power(int pwr);
	int get_hp() const;
	int get_armor() const;
	int get_power() const;
protected:
	int health;
	int armor;
	int power;
};

#endif
