#ifndef SAVE_LOAD_STATE_H
#define SAVE_LOAD_STATE_H

#include "panel_state.h"
#include "../ui/save_load_panel.h"

class Game;

class SaveLoadState : public PanelState {
public:
	SaveLoadState(Game& g, bool save);
	void save_or_load(size_t slot);

private:
	void save(size_t slot);
	void load(size_t slot);
	bool saving;
};


#endif
