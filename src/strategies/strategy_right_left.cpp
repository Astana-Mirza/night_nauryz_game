#include "../../inc/strategies/strategy_right_left.h"

StrategyRightLeft::StrategyRightLeft(bool r) : right{r} {}

void StrategyRightLeft::execute(Movable& el) {
	bool ok;
	if (right) {
		ok = el.move({1, 0});
		if (!ok) el.move({-1, 0});
	} else {
		ok = el.move({-1, 0});
		if (!ok) el.move({1, 0});
	}
	if (!ok)
		right = !right;
}

