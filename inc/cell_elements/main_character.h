#ifndef MAIN_CHARACTER_H
#define MAIN_CHARACTER_H

#include "../interfaces/player.h"
#include "../actions/action_picked_up.h"
#include "abstract/attackable_element.h"
#include "../input_commands/player_command_handler.h"

class MainCharacter : public AttackableElement, public Player {
public:
	MainCharacter(IGameplayManager& gm, int hp,
				int arm, int pwr, Point2D pos);
	bool move_to(Point2D r);
	void update();
	std::shared_ptr<CommandHandler> get_command_handler() const;
	void set_move_dest(Point2D pos);
	void pickup(PickupItem& it);
	std::shared_ptr<CellElement> clone() const;
	void destroy();
	bool interact(CellElement& el);
	bool interact(Enemy& el);
	bool interact(PickupItem& el);
	bool interact(Player& el);

private:
	std::shared_ptr<CommandHandler> command_handler;
	Point2D move_dest;
};

#endif
