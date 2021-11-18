#ifndef MAX_STEPS_RULE_H
#define MAX_STEPS_RULE_H

#include "../interfaces/igameplay_manager.h"

template <size_t N>
struct MaxStepsRule {
	bool check_rule(const IGameplayManager& gm) const {
		return gm.get_player_steps() <= N;
	}
};

#endif
