#include "../../inc/strategies/strategy_up_down.h"

StrategyUpDown::StrategyUpDown(bool d) : down{d} {}
void StrategyUpDown::accept(Visitor& vis) { vis.visit(*this); }
bool StrategyUpDown::get_direction() const { return down; }

void StrategyUpDown::execute(Movable& el) {
	bool ok;
	if (down) {
		ok = el.move({0, 1});
		if (!ok) el.move({0, -1});
	} else {
		ok = el.move({0, -1});
		if (!ok) el.move({0, 1});
	}
	if (!ok)
		down = !down;
}
