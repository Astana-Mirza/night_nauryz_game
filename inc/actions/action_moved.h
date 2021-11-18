#ifndef ACTION_MOVED_H
#define ACTION_MOVED_H

#include "../interfaces/action_object.h"
#include "../point2d.h"

class ActionMoved : public ActionObject {
public:
	ActionMoved(const CellElement& s, Point2D to) :
			sender(s), dest{to} {}

	void handle_action(ActionListener& al) const {
		al.handle_move(sender, dest);
	}

private:
	const CellElement& sender;
	Point2D dest;
};

#endif

