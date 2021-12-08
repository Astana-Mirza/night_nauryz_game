#include "../../inc/utility/serial_file_visitor.h"

SerialFileVisitor::SerialFileVisitor(Field& f, size_t killed,
	size_t step, size_t coins) : field{f}, enemies_killed{killed},
	steps{step}, coins_picked{coins} {}


void SerialFileVisitor::save_field(const std::string& filename) {
	outfile.open(filename);
	if (!outfile.is_open()) {
		throw FileError{"unable to open file", filename};
	}
	outfile << true	<< ' '		// saving difficulty
		<< static_cast<int>(ConfigManager::instance().difficulty)
		<< ' ';
	outfile << enemies_killed << ' '
		<< steps << ' '
		<< coins_picked << ' ';
	outfile << field.get_height() << ' ' << field.get_width() << std::endl;
	for (auto& cell : field) {
		cell.accept(*this);
	}
}

void SerialFileVisitor::visit(const Cell& cell) {
	outfile << "Cell ";
	serialize_cell(cell);
}

void SerialFileVisitor::visit(const StartCell& cell) {
	outfile << "StartCell ";
	serialize_cell(cell);
}

void SerialFileVisitor::visit(const FinishCell& cell) {
	outfile << "FinishCell ";
	serialize_cell(cell);
}

void SerialFileVisitor::serialize_cell(const Cell& cell) {
	outfile << cell.is_passable();
	auto& element = cell.get_element();
	if (element) {
		if (!cell.is_passable()) {
			throw WallError{"element in wall"};
		}
		outfile << ' ' << true;
		element->accept(*this);
	} else {
		outfile << ' ' << false;
	}
	outfile << std::endl;
}


void SerialFileVisitor::serialize_attackable_el(const AttackableElement& el) {
	int hp = el.get_hp(), armor =  el.get_armor(), power = el.get_power();
	if (hp <= 0 || armor < 0 || power < 0) {
		throw GameError{"wrong entity characteristic"};
	}
	outfile << el.get_hp() << ' ' << el.get_armor() << ' ' << el.get_power();
}


void SerialFileVisitor::serialize_base_pickup(const BasePickupItem& el) {
	outfile << el.get_characteristic();
}


void SerialFileVisitor::visit(const MainCharacter& el) {
	outfile << " MainCharacter ";
	serialize_attackable_el(el);
}

void SerialFileVisitor::visit(const RegularEnemy& el) {
	outfile << " RegularEnemy ";
	serialize_attackable_el(el);
	outfile << ' ' << el.has_strategy();
}

void SerialFileVisitor::visit(const SupportEnemy& el) {
	outfile << " SupportEnemy ";
	serialize_attackable_el(el);
	outfile << ' ' << el.has_strategy();
}

void SerialFileVisitor::visit(const VampireEnemy& el) {
	outfile << " VampireEnemy ";
	serialize_attackable_el(el);
	outfile << ' ' << el.has_strategy();
}

void SerialFileVisitor::visit(const Healer& el) {
	outfile << " Healer ";
	serialize_base_pickup(el);
}

void SerialFileVisitor::visit(const Shield& el) {
	outfile << " Shield ";
	serialize_base_pickup(el);
}

void SerialFileVisitor::visit(const PowerUp& el) {
	outfile << " PowerUp ";
	serialize_base_pickup(el);
}

void SerialFileVisitor::visit(const Coin& el) {
	outfile << " Coin";
}

void SerialFileVisitor::visit(const StrategyRightLeft& st) {
	outfile << " RL " << st.get_direction();
}

void SerialFileVisitor::visit(const StrategyUpDown& st) {
	outfile << " UD " << st.get_direction();
}
