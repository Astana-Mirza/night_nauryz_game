#ifndef IGAMEPLAY_MANAGER_H
#define IGAMEPLAY_MANAGER_H

#include "../field.h"

class IGameplayManager {
public:
	virtual void game_over() =0;
	virtual void level_completed() =0;
	virtual void game_paused() =0;

	virtual void player_moved() =0;
	virtual void enemy_killed() =0;
	virtual void coin_picked() =0;

	virtual size_t get_player_steps() const =0;
	virtual size_t get_killed_count() const =0;
	virtual size_t get_coin_count() const =0;

	//virtual void set_field(Field&& f) =0;
	virtual Cell& get_cell(Point2D pos) const =0;
	virtual void add_object(const std::shared_ptr<CellElement>& obj) =0;
	virtual void object_expired(const std::shared_ptr<CellElement>& obj) =0;
	virtual ~IGameplayManager() =default;
};

#endif
