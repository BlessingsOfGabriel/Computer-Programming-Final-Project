#ifndef STATUS_H
#define STATUS_H
#include "Obj.h"
#include "Unit.h"
#include "global.h"

class Status: public Obj{
public:
    Status();
    ~Status();
	int calculate_gpt();
	void turn_plus();
	void add_Unit(Unit);
	void delete_Unit(int,int);
	void minus_gold(int);
	bool valid_buy(UnitType);

protected:
	int _goldPerTurn;
	int _goldAmount;
	int _turn;
	std::vector<Unit> _unitList;
};
#endif
