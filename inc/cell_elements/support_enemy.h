#ifndef SUPPORT_ENEMY_H
#define SUPPORT_ENEMY_H

#include "regular_enemy.h"

class SupportEnemy : public RegularEnemy {
public:
	using RegularEnemy::RegularEnemy;
	std::shared_ptr<CellElement> clone() const;
	bool interact(Player& el);
	bool interact(Enemy& el);
};

#endif
