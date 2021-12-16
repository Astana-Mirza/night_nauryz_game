#include "../../inc/cell_elements/vampire_enemy.h"

std::shared_ptr<CellElement> VampireEnemy::clone() const {
	return std::make_shared<VampireEnemy>(gameplay, health, armor,
						power, position);
}


void VampireEnemy::accept(Visitor& vis) {
	vis.visit(*this);
	if (strategy)
		strategy->accept(vis);
}


bool VampireEnemy::interact(Player& el) {
	int dmg = el.calculate_damage(power);
	send_action(ActionAttacked(*this, dmg,
		dynamic_cast<AttackableElement&>(
			static_cast<Attackable&>(el))));
	el.change_hp(-dmg);
	change_hp(dmg);
	return true;
}
