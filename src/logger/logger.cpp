#include "../../inc/logger/logger.h"

Logger::Logger(bool console, bool file, const std::string& filename) :
		write_to_console{console} {
	if (file) {
		outfile.open(filename);
		if (!outfile.is_open()) {
			throw FileError{"unable to open file", filename};
		}
	}
	write_log("---------------[LOG STARTED]---------------\n");
}


Logger::~Logger() {
	write_log("---------------[LOG ENDED]---------------\n");
}


void Logger::set_console_output(bool set, bool flush_lines) {
	if (set) {
		std::clog << "---------------[LOG CONTINUED]---------------\n";
	} else if (write_to_console) {
		std::clog << "---------------[LOG INTERRUPTED]---------------\n";
	}
	write_to_console = set;
	flush = flush_lines;
}


void Logger::set_file_output(bool set, const std::string& filename) {
	if (set) {
		outfile.open(filename);
		outfile << "---------------[LOG CONTINUED]---------------\n";
	} else if (outfile.is_open()) {
		outfile << "---------------[LOG INTERRUPTED]---------------\n";
		outfile.close();
	}
}


void Logger::write_log(const std::string& log) {
	if (write_to_console) {
		if (flush)
			std::cerr << log;
		else
			std::clog << log;
	}
	if (outfile.is_open()) {
		outfile << log;
	}
}


void Logger::handle_move(const CellElement& el, Point2D pos) {
	std::stringstream buf;
	buf << el << " moved to " << pos << '\n';
	write_log(buf.str());
}


void Logger::handle_destruction(const CellElement& el) {
	std::stringstream buf;
	buf << el << " destroyed\n";
	write_log(buf.str());
}


void Logger::handle_attack(const CellElement& el, int dmg,
			const CellElement& victim) {
	std::stringstream buf;
	buf << el << " attacked " <<
		victim << " and caused " << dmg << " damage\n";
	write_log(buf.str());
}


void Logger::handle_charact_change(const CellElement& el,
		int prev, int curr, Characteristic c) {
	std::string charact;
	switch (c) {
		case Characteristic::Health:
			charact = "health";
		break;
		case Characteristic::Armor:
			charact = "armor";
		break;
		case Characteristic::Power:
			charact = "power";
		break;
	}
	std::stringstream buf;
	buf << el << " changed its " << charact <<
		" from " << prev << " to " << curr << '\n';
	write_log(buf.str());
}


void Logger::handle_pickup(const CellElement& el, bool is_picker) {
	std::string sense = is_picker ? " picked up an item" : " was picked";
	std::stringstream buf;
	buf << el << sense << std::endl;
	write_log(buf.str());
}
