#ifndef BOARD_H
#define BOARD_H
#include "Obj.h"
#include "Unit.h"

class Board: public Obj{
public:
	Board();
	~Board();
	void add_unit(int posX, int posY, Unit new_unit);
	void delete_unit(int posX, int posY);


protected:
	Unit* _current;
	
};
#endif