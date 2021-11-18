#include "../../inc/logger/base_logger_decorator.h"

BaseLoggerDecorator::BaseLoggerDecorator(std::unique_ptr<ILogger>&& ptr) :
	wrappee{std::move(ptr)} {}

void BaseLoggerDecorator::set_console_output(bool set, bool flush_lines) {
	wrappee->set_console_output(set, flush_lines);
}

void BaseLoggerDecorator::set_file_output(bool set,
				const std::string& filename) {
	wrappee->set_file_output(set, filename);
}


void BaseLoggerDecorator::write_log(const std::string& log) {
	wrappee->write_log(log);
}
