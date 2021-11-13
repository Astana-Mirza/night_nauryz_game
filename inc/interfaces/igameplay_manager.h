#ifndef IGAMEPLAY_MANAGER_H
#define IGAMEPLAY_MANAGER_H

#include "../field.h"

class IGameplayManager {
public:
	virtual void update(double delta) =0;
	virtual void game_over() =0;
	virtual void level_completed() =0;
	/*virtual void player_moved() =0;
	virtual void enemy_killed() =0;
	virtual void coin_picked() =0;*/
	//virtual void set_field(Field&& f) =0;
	virtual Cell& get_cell(Point2D pos) const =0;
	virtual void object_expired(const std::shared_ptr<CellElement>& obj) =0;
	virtual ~IGameplayManager() =default;
};

#endif
