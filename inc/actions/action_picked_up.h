#ifndef ACTION_PICKED_UP_H
#define ACTION_PICKED_UP_H

#include "../interfaces/action_object.h"

class ActionPickedUp : public ActionObject {
public:
	ActionPickedUp(const CellElement& s, bool picker=true) :
				sender{s}, is_picker{picker} {}

	void handle_action(ActionListener& al) const {
		al.handle_pickup(sender, is_picker);
	}

private:
	const CellElement& sender;
	bool is_picker;
};

#endif

