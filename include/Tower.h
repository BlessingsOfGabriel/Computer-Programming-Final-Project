#ifndef TOWER_H
#define TOWER_H
#include "Unit.h"
#include "Obj.h"

class Tower:public Unit{
    public:
        Tower();
        ~Tower();
        bool valid_attack(int posX,int posY);
        bool valid_move(int posX,int posY);
        bool valid_pos(int posX,int posY)
}

#endif
