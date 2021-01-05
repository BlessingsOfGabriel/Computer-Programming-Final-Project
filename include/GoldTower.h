#ifndef GOLDTOWER_H
#define GOLDTOWER_H
#include "Unit.h"
#include "Obj.h"

class GoldTower:public Unit{
public:
        GoldTower(int);
        ~GoldTower();
        bool valid_attack(int posX,int posY);
        bool valid_move(int posX,int posY);
        bool valid_pos(int posX,int posY);

};
#endif
