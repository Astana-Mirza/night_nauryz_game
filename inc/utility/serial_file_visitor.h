#ifndef SERIAL_FILE_VISITOR_H
#define SERIAL_FILE_VISITOR_H

#include <string>
#include <fstream>
#include "../interfaces/visitor.h"
#include "config_manager.h"

#include "../cells/cell.h"
#include "../cells/start_cell.h"
#include "../cells/finish_cell.h"
#include "../cell_elements/main_character.h"
#include "../cell_elements/regular_enemy.h"
#include "../cell_elements/support_enemy.h"
#include "../cell_elements/vampire_enemy.h"
#include "../cell_elements/healer.h"
#include "../cell_elements/power_up.h"
#include "../cell_elements/shield.h"
#include "../cell_elements/coin.h"
#include "../strategies/strategy_right_left.h"
#include "../strategies/strategy_up_down.h"
#include "../field.h"
#include "../exception/file_error.h"
#include "../exception/wall_error.h"

class SerialFileVisitor : public Visitor {
public:
	SerialFileVisitor(Field& f, size_t killed,
			size_t step, size_t coins);
	void save_field(const std::string& filename);
	void visit(const Cell& cell);
	void visit(const StartCell& cell);
	void visit(const FinishCell& cell);
	void visit(const MainCharacter& el);
	void visit(const RegularEnemy& el);
	void visit(const SupportEnemy& el);
	void visit(const VampireEnemy& el);
	void visit(const Healer& el);
	void visit(const Shield& el);
	void visit(const PowerUp& el);
	void visit(const Coin& el);
	void visit(const StrategyRightLeft& st);
	void visit(const StrategyUpDown& st);

private:
	void serialize_cell(const Cell& cell);
	void serialize_attackable_el(const AttackableElement& el);
	void serialize_base_pickup(const BasePickupItem& el);

	Field& field;
	size_t enemies_killed, steps, coins_picked;
	std::ofstream outfile;
};

#endif
