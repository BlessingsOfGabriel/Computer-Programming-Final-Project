#ifndef STATUS_H
#define STATUS_H
#include "Obj.h"
#include "Unit.h"
class status: public Obj{
public:
	int calculate_gpt();
	void turn_plus();
	void add_Unit(Unit);
	void delete_Unit(int,int);

protected:
	int _goldPerTurn;
	int _goldAmount;
	int _turn;
	std::vector<Unit> _unitList;
};
#endif
