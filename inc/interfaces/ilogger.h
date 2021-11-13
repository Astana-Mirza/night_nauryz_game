#ifndef ILOGGER_H
#define ILOGGER_H

#include <string>
#include "action_listener.h"

class ILogger : public ActionListener {
public:
	virtual void set_console_output(bool set, bool flush_lines) =0;
	virtual void set_file_output(bool set, const std::string& filename) =0;
	virtual void write_log(const std::string& log) =0;
};

#endif
