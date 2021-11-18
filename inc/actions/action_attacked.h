#ifndef ACTION_ATTACKED_H
#define ACTION_ATTACKED_H

#include "../interfaces/action_object.h"
#include "../interfaces/attackable.h"

class ActionAttacked : public ActionObject {
public:
	ActionAttacked(const CellElement& s, int dmg, const CellElement& v) :
			sender{s}, victim{v}, damage{dmg} {}

	void handle_action(ActionListener& al) const {
		al.handle_attack(sender, damage, victim);
	}

private:
	const CellElement& sender;
	const CellElement& victim;
	int damage;
};

#endif
