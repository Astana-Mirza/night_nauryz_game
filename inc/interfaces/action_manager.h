#ifndef ACTION_MANAGER_H
#define ACTION_MANAGER_H

#include <memory>
#include "action_object.h"
#include "action_listener.h"

class ActionManager {
public:
	virtual void subscribe(const std::shared_ptr<ActionListener>& listener) =0;
	virtual void unsubscribe(const std::shared_ptr<ActionListener>& listener) =0;
	virtual void unsubscribe_all() =0;
	virtual void send_action(const ActionObject& act) const =0;
	virtual ~ActionManager()=default;
};

#endif
