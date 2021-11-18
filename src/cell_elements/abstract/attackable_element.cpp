#include "../../../inc/cell_elements/abstract/attackable_element.h"

AttackableElement::AttackableElement(IGameplayManager& gm, int hp, int arm,
							int pwr, Point2D p):
		MovableElement::MovableElement(gm, p),
		health{hp}, armor{arm}, power{pwr} {}


int AttackableElement::calculate_damage(int power) const {
	if (power > 0) {
		power = armor >= power ? 0 : power - armor;
		return power;
	}
	return 0;
}


int AttackableElement::change_hp(int hp) {
	int prev = health;
	health += hp;
	if (health - prev) {
		send_action(ActionCharactChanged(*this, prev, health,
				ActionListener::Characteristic::Health));
	}
	if (health <= 0) {
		destroy();
	}
	return health-prev;
}


int AttackableElement::change_armor(int arm) {
	int prev = armor;
	armor = armor > -arm ? armor+arm : 0;
	if (armor - prev) {
		send_action(ActionCharactChanged(*this, prev, armor,
				ActionListener::Characteristic::Armor));
	}
	return armor-prev;
}


int AttackableElement::change_power(int pwr) {
	int prev = power;
	power = power > -pwr ? power+pwr : 0;
	if (power - prev) {
		send_action(ActionCharactChanged(*this, prev, power,
				ActionListener::Characteristic::Power));
	}
	return power-prev;
}


int AttackableElement::get_hp() const { return health; }

int AttackableElement::get_armor() const { return armor; }

int AttackableElement::get_power() const { return power; }
