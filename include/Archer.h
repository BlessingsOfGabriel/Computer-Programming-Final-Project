#ifndef ARCHER_H
#define ARCHER_H
#include "Unit.h"
#include "Obj.h"

class Archer: public Unit{
public:
    Archer(int);
    ~Archer();
    bool valid_move(int posX,int posY);
    bool valid_attack(int posX,int posY);
    bool valid_pos(int posX,int posY);

};

#endif
