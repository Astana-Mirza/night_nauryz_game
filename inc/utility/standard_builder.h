#ifndef STANDARD_BUILDER_H
#define STANDARD_BUILDER_H

#include <fstream>
#include <sstream>
#include "config_manager.h"
#include "../rules/coins_picked_rule.h"
#include "../rules/enemies_killed_rule.h"
#include "../rules/max_steps_rule.h"
#include "../interfaces/gameplay_builder.h"
#include "../interfaces/render_engine.h"
#include "../interfaces/ilogger.h"
#include "../cell_elements/main_character.h"
#include "../cell_elements/power_up.h"
#include "../cell_elements/healer.h"
#include "../cell_elements/shield.h"
#include "../cell_elements/coin.h"
#include "../cell_elements/regular_enemy.h"
#include "../cell_elements/support_enemy.h"
#include "../cell_elements/vampire_enemy.h"
#include "../strategies/strategy_right_left.h"
#include "../strategies/strategy_up_down.h"
#include "../cells/finish_cell.h"
#include "../cells/start_cell.h"
#include "../game.h"
#include "../states/info_state.h"
#include "../exception/parse_error.h"
#include "../exception/wall_error.h"

template <typename... Rules>
class GameplayState;

class StandardBuilder : public GameplayBuilder {
public:
	StandardBuilder(Game& gm);
	bool load(const std::string& saved_level);
	std::unique_ptr<GameState> get_result();

private:
	void read_line();
	void read_header();
	void read_characteristics(int& hp, int& armor,
				int& power, bool& has_strategy, bool strat);
	void load_cells(IGameplayManager& st, CommandHandler& ch);
	void spawn_element(IGameplayManager& st, CommandHandler& ch, Point2D pos);
	std::unique_ptr<Strategy> read_strategy();
	void add_object(IGameplayManager& st,
			const std::shared_ptr<CellElement>& obj,
			const std::string& texture);

	Game& game;
	size_t line_num;
	std::unique_ptr<GameState> state;
	Field current_field;
	std::string current_filename;
	std::ifstream infile;
	std::stringstream current_line;
};

#endif
