#ifndef SAVE_LOAD_STATE_H
#define SAVE_LOAD_STATE_H

#include <string>
#include "panel_state.h"
#include "../interfaces/visitor.h"
#include "../ui/save_load_panel.h"
#include "../utility/standard_builder.h"

class Game;

class SaveLoadState : public PanelState {
public:
	SaveLoadState(Game& g, const std::shared_ptr<Visitor>& sv=nullptr);
	void save_or_load(const std::string& filename);

private:
	std::shared_ptr<Visitor> saver;
};


#endif
