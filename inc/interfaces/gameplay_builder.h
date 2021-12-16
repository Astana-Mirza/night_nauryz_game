#ifndef GAMEPLAY_BUILDER_H
#define GAMEPLAY_BUILDER_H

#include "game_state.h"

class GameplayBuilder {
public:
	virtual bool load(const std::string& saved_level) =0;
	virtual std::unique_ptr<GameState> get_result() =0;
	virtual ~GameplayBuilder() =default;
};

#endif
