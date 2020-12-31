#ifndef STATUS_H
#define STATUS_H
#include "Obj.h"
class status: public Obj{
public:
	int calculate_gpt(); 
protected:
	int _goldPerTurn;
	int _gold_amount;
};
#endif
