#ifndef STANDARD_BUILDER_H
#define STANDARD_BUILDER_H

#include "config_manager.h"
#include "../interfaces/field_builder.h"
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

class StandardBuilder : public FieldBuilder {
public:
	StandardBuilder(IGameplayManager& gm,
			const std::shared_ptr<RenderEngine>& paint,
			const std::shared_ptr<ILogger>& log,
			const std::shared_ptr<CommandHandler>& ch);
	void reset(const std::string& saved_level);
	void setup_cells();
	void spawn_elements();
	Field&& get_result();

private:
	void add_object(const std::shared_ptr<CellElement>& obj,
			const std::string& texture);

	IGameplayManager& gameplay;
	std::shared_ptr<RenderEngine> painter;
	std::shared_ptr<ILogger> logger;
	std::shared_ptr<CommandHandler> command_handler;
	Field current_field;
};

#endif
