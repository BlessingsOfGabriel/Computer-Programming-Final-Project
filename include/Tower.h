#ifndef TOWER_H
#define TOWER_H
#include "Unit.h"
#include "Obj.h"

Class Tower:public Unit{
    public:
        Tower();
        ~Tower();
        bool valid_attack(int posX,int posY);
}

#endif
