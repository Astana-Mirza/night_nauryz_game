#ifndef TIME_LOGGER_DECORATOR_H
#define TIME_LOGGER_DECORATOR_H

#include <ctime>
#include "base_logger_decorator.h"

class TimeLoggerDecorator : public BaseLoggerDecorator {
public:
	using BaseLoggerDecorator::BaseLoggerDecorator;
	void handle_move(const CellElement& el, Point2D pos);
	void handle_destruction(const CellElement& el);
	void handle_attack(const CellElement& el, int dmg,
				const CellElement& victim);
	void handle_charact_change(const CellElement& el,
				int prev, int curr, Characteristic c);
	void handle_pickup(const CellElement& el, bool is_picker);
private:
	const std::string get_time() const;
};

#endif
