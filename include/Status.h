#ifndef STATUS_H
#define STATUS_H
#include "Obj.h"
class status: public Obj{
public:
	int calculate_gpt();
	void turn_plus();

protected:
	int _goldPerTurn;
	int _goldAmount;
	int _turn;
};
#endif
