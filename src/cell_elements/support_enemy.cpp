#include "../../inc/cell_elements/support_enemy.h"

std::shared_ptr<CellElement> SupportEnemy::clone() const {
	return std::make_shared<SupportEnemy>(gameplay, health, armor,
						power, position);
}


void SupportEnemy::accept(Visitor& vis) {
	vis.visit(*this);
	if (strategy)
		strategy->accept(vis);
}


bool SupportEnemy::interact(Player& el) {
	int dmg = el.change_armor(-power);
	send_action(ActionAttacked(*this, -dmg,
		dynamic_cast<AttackableElement&>(
			static_cast<Attackable&>(el))));
	return true;
}


bool SupportEnemy::interact(Enemy& el) {
	el.change_hp(1);
	return false;
}
