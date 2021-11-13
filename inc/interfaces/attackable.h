#ifndef ATTACKABLE_H
#define ATTACKABLE_H

class Attackable {
public:
	virtual int calculate_damage(int power) const =0;
	virtual int change_hp(int hp) =0;
	virtual int change_armor(int arm) =0;
	virtual int change_power(int pwr) =0;
	virtual ~Attackable() =default;
};

#endif
