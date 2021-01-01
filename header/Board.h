#ifndef BOARD_H
#define BOARD_H
#include "Obj.h"
#include "Unit.h"

class Board: public Obj{
public:
	Board();
	~Board();
protected:
	Unit* _current;
};
#endif
