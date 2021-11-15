#ifndef COINS_PICKED_RULE_H
#define COINS_PICKED_RULE_H

#include "../interfaces/igameplay_manager.h"

template <size_t N>
struct CoinsPickedRule {
	bool check_rule(const IGameplayManager& gm) const {
		return gm.get_coin_count() >= N;
	}
};

#endif
