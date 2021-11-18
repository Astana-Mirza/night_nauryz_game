#ifndef ACTION_LISTENER_H
#define ACTION_LISTENER_H

#include "../point2d.h"
#include "cell_element.h"
#include "action_object.h"

class ActionObject;

class ActionListener {
public:
	enum class Characteristic {Health, Armor, Power};
	virtual void handle_move(const CellElement& el, Point2D pos) =0;
	virtual void handle_destruction(const CellElement& el) =0;
	virtual void handle_attack(const CellElement& el, int dmg,
					const CellElement& victim) =0;
	virtual void handle_charact_change(const CellElement& el,
			int prev, int curr, Characteristic c) =0;
	virtual void handle_pickup(const CellElement& el, bool is_picker) =0;
	virtual ~ActionListener()=default;
};

#endif
