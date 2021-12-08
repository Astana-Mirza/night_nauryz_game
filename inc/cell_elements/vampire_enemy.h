#ifndef VAMPIRE_ENEMY_H
#define VAMPIRE_ENEMY_H

#include "regular_enemy.h"

class VampireEnemy : public RegularEnemy {
public:
	using RegularEnemy::RegularEnemy;
	std::shared_ptr<CellElement> clone() const;
	void accept(Visitor& vis);
	bool interact(Player& el);
};

#endif
