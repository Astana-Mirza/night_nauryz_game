#ifndef ACTION_OBJECT_H
#define ACTION_OBJECT_H

#include "action_listener.h"

class ActionListener;

class ActionObject {
public:
	virtual void handle_action(ActionListener& al) const =0;
	virtual ~ActionObject()=default;
};

#endif
