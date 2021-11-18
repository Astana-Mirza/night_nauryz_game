#ifndef ACTION_DESTROYED_H
#define ACTION_DESTROYED_H

#include "../interfaces/action_object.h"

class ActionDestroyed : public ActionObject {
public:
	ActionDestroyed(const CellElement& s) : sender{s} {}

	void handle_action(ActionListener& al) const {
		al.handle_destruction(sender);
	}

private:
	const CellElement& sender;
};

#endif

