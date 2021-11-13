#include "../../inc/cell_elements/regular_enemy.h"

std::shared_ptr<CellElement> RegularEnemy::clone() const {
	return std::make_shared<RegularEnemy>(gameplay, health, armor,
						power, position);
}


void RegularEnemy::set_strategy(std::unique_ptr<Strategy>&& s) {
	strategy = std::move(s);
}


bool RegularEnemy::interact(Player& el) {
	int dmg = el.calculate_damage(power);
	send_action(ActionAttacked(*this, dmg,
		dynamic_cast<AttackableElement&>(
			static_cast<Attackable&>(el))));
	el.change_hp(-dmg);
	return true;
}

bool RegularEnemy::interact(CellElement& el) { return el.interact((Enemy&)*this); }

bool RegularEnemy::interact(Enemy& el) { return false; }

bool RegularEnemy::interact(PickupItem& el) { return false; }

void RegularEnemy::update() { strategy->execute(*this); }
