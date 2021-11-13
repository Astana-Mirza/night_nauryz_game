#include "../../inc/actions/base_action_manager.h"

void BaseActionManager::subscribe(const std::shared_ptr<ActionListener>& listener) {
	subscribers.insert(listener);
}


void BaseActionManager::unsubscribe(const std::shared_ptr<ActionListener>& listener) {
	auto it = subscribers.find(listener);
	if (it != subscribers.end()) {
		subscribers.erase(it);
	}
}


void BaseActionManager::unsubscribe_all() {
	subscribers.erase(subscribers.begin(), subscribers.end());
}


void BaseActionManager::send_action(const ActionObject& act) const {
	for (auto& s : subscribers) {
		act.handle_action(*s);
	}
}
