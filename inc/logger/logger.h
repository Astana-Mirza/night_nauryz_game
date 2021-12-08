#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "../interfaces/ilogger.h"
#include "stream_operators.h"
#include "../exception/file_error.h"

class Logger: public ILogger {
public:
	Logger(bool console=true, bool file=false,
					const std::string& filename="log.txt");
	~Logger();
	void set_console_output(bool set, bool flush_lines=false);
	void set_file_output(bool set, const std::string& filename="log.txt");
	void write_log(const std::string& log);

	void handle_move(const CellElement& el, Point2D pos);
	void handle_destruction(const CellElement& el);
	void handle_attack(const CellElement& el, int dmg,
				const CellElement& victim);
	void handle_charact_change(const CellElement& el,
				int prev, int curr, Characteristic c);
	void handle_pickup(const CellElement& el, bool is_picker);
private:
	bool write_to_console;
	bool flush = false;
	std::ofstream outfile;
};

#endif
