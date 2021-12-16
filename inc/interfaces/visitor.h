#ifndef VISITOR_H
#define VISITOR_H

#include <string>

class Cell;
class StartCell;
class FinishCell;
class MainCharacter;
class RegularEnemy;
class SupportEnemy;
class VampireEnemy;
class Healer;
class Shield;
class PowerUp;
class Coin;
class StrategyRightLeft;
class StrategyUpDown;

class Visitor {
public:
	virtual void save_field(const std::string& filename) =0;
	virtual void visit(const Cell& cell) =0;
	virtual void visit(const StartCell& cell) =0;
	virtual void visit(const FinishCell& cell) =0;
	virtual void visit(const MainCharacter& el) =0;
	virtual void visit(const RegularEnemy& el) =0;
	virtual void visit(const SupportEnemy& el) =0;
	virtual void visit(const VampireEnemy& el) =0;
	virtual void visit(const Healer& el) =0;
	virtual void visit(const Shield& el) =0;
	virtual void visit(const PowerUp& el) =0;
	virtual void visit(const Coin& el) =0;
	virtual void visit(const StrategyRightLeft& st) =0;
	virtual void visit(const StrategyUpDown& st) =0;
	virtual ~Visitor() =default;
};

#endif
