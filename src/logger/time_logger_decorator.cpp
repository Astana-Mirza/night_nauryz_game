#include "../../inc/logger/time_logger_decorator.h"

const std::string TimeLoggerDecorator::get_time() const {
    std::time_t now = std::time(0);
    std::tm tstruct;
    char buf[80];
    tstruct = *std::localtime(&now);
    std::strftime(buf, sizeof(buf), "[%d-%m-%Y %X]\t", &tstruct);
    return buf;
}


void TimeLoggerDecorator::handle_move(const CellElement& el, Point2D pos) {
	write_log(get_time());
	wrappee->handle_move(el, pos);
}


void TimeLoggerDecorator::handle_destruction(const CellElement& el) {
	write_log(get_time());
	wrappee->handle_destruction(el);
}

void TimeLoggerDecorator::handle_attack(const CellElement& el, int dmg,
			const CellElement& victim) {
	write_log(get_time());
	wrappee->handle_attack(el, dmg, victim);
}


void TimeLoggerDecorator::handle_charact_change(const CellElement& el,
			int prev, int curr, Characteristic c) {
	write_log(get_time());
	wrappee->handle_charact_change(el, prev, curr, c);
}


void TimeLoggerDecorator::handle_pickup(const CellElement& el, bool is_picker) {
	write_log(get_time());
	wrappee->handle_pickup(el, is_picker);
}
