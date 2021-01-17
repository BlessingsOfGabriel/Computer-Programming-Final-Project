#ifndef BOARD_H
#define BOARD_H
#include "Obj.h"
#include "Unit.h"

class Board: public Obj{
public:
	Board();
	~Board();
	void add_unit(int posX, int posY, Unit* new_unit);
	void delete_unit(int posX, int posY);
    void move(int x,int y,int posX,int posY);
    void attack(int x,int y,int posX,int posY);
    Unit* getUnit(int x,int y);
    int get_base0();
    int get_base1();


protected:
	Unit* **_current;
    int _base0;
    int _base1;
};
#endif

extern Board gBoard;
