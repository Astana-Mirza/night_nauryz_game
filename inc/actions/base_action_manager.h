#ifndef BASE_ACTION_MANAGER_H
#define BASE_ACTION_MANAGER_H

#include <set>
#include "../interfaces/action_manager.h"

class BaseActionManager : public ActionManager {
public:
	void subscribe(const std::shared_ptr<ActionListener>& listener);
	void unsubscribe(const std::shared_ptr<ActionListener>& listener);
	void unsubscribe_all();
	void send_action(const ActionObject& act) const;

private:
	std::set<std::shared_ptr<ActionListener>> subscribers;
};

#endif

