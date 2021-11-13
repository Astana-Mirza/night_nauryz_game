#ifndef BASE_LOGGER_DECORATOR_H
#define BASE_LOGGER_DECORATOR_H

#include <memory>
#include "../interfaces/ilogger.h"

class BaseLoggerDecorator : public ILogger {
public:
	BaseLoggerDecorator(std::unique_ptr<ILogger>&& ptr);
	void set_console_output(bool set, bool flush_lines=false);
	void set_file_output(bool set, const std::string& filename="log.txt");
	void write_log(const std::string& log);

protected:
	std::unique_ptr<ILogger> wrappee;
};

#endif
