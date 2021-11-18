#ifndef BASE_CELL_ELEMENT_H
#define BASE_CELL_ELEMENT_H

#include "../../actions/base_action_manager.h"
#include "../../interfaces/cell_element.h"
#include "../../actions/action_destroyed.h"
#include "../../interfaces/igameplay_manager.h"
#include <functional>

class BaseCellElement : public BaseActionManager, public CellElement {
public:
	BaseCellElement(IGameplayManager& gm, Point2D pos);
	void update() {}
	void destroy();
	size_t get_id() const;
	Point2D get_pos() const;

protected:
	IGameplayManager& gameplay;
	Point2D position;
};

#endif
