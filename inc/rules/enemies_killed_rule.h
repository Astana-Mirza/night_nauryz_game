#ifndef ENEMIES_KILLED_RULE_H
#define ENEMIES_KILLED_RULE_H

#include "../interfaces/igameplay_manager.h"

template <size_t N>
struct EnemiesKilledRule {
	bool check_rule(const IGameplayManager& gm) const {
		return gm.get_killed_count() >= N;
	}
};

#endif
