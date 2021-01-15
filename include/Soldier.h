#ifndef SOLDIER_H
#define SOLDIER_H
#include "Unit.h"
#include "Obj.h"

class Soldier: public Unit{
public:
    Soldier(int);
    ~Soldier();
    bool valid_move(int posX,int posY);
    bool valid_attack(int posX,int posY);
    bool valid_pos(int posX,int posY);

};

#endif