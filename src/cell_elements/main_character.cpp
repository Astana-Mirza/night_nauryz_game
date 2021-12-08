#include "../../inc/cell_elements/main_character.h"

MainCharacter::MainCharacter(IGameplayManager& gm, int hp,
			int arm, int pwr, Point2D pos) :
		AttackableElement::AttackableElement(gm, hp, arm, pwr, pos) {
	command_handler = std::make_shared<PlayerCommandHandler>(*this);
}


bool MainCharacter::move_to(Point2D r) {
	//auto& prev = gameplay.get_cell(position);
	bool ok = AttackableElement::move_to(r);
	auto& curr = gameplay.get_cell(r);
	if (ok) {
		//prev.player_exited();
		curr.player_entered();
		gameplay.player_moved();
	}
	return ok;
}


void MainCharacter::set_move_dest(Point2D pos) {
	move_dest = pos;
}


void MainCharacter::update() {
	if (move_dest != Point2D{0, 0})
		move(move_dest);
	move_dest = {0, 0};
}


std::shared_ptr<CommandHandler> MainCharacter::get_command_handler() const {
	return command_handler;
}


void MainCharacter::pickup(PickupItem& it) {
	it.give_effect(*this);
	send_action(ActionPickedUp(*this));
}


bool MainCharacter::interact(Enemy& el) {
	int dmg = el.calculate_damage(power);
	send_action(ActionAttacked(*this, dmg,
		dynamic_cast<AttackableElement&>(
			static_cast<Attackable&>(el))));
	el.change_hp(-dmg);
	return true;
}


std::shared_ptr<CellElement> MainCharacter::clone() const {
	return std::make_shared<MainCharacter>(gameplay, health,
				armor, power, position);
}

void MainCharacter::destroy() {
	auto& gm = gameplay;
	AttackableElement::destroy();
	gm.game_over();
}

bool MainCharacter::interact(PickupItem& el) {
	pickup(el);
	return true;
}

void MainCharacter::accept(Visitor& vis) { vis.visit(*this); }
bool MainCharacter::interact(CellElement& el) { return el.interact((Player&)*this); }
bool MainCharacter::interact(Player& el) { return false; }
