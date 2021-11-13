#ifndef ACTION_CHARACT_CHANGED_H
#define ACTION_CHARACT_CHANGED_H

#include "../interfaces/action_object.h"

class ActionCharactChanged : public ActionObject {
public:
	ActionCharactChanged(const CellElement& s, int pr, int curr,
				ActionListener::Characteristic c) :
			sender{s}, prev{pr}, current{curr}, ch{c} {}

	void handle_action(ActionListener& al) const {
		al.handle_charact_change(sender, prev, current, ch);
	}

private:
	const CellElement& sender;
	int prev, current;
	ActionListener::Characteristic ch;
};

#endif

