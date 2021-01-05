#ifndef KNIGHT_H
#define KNIGHT_H
#include "Unit.h"
#include "Obj.h"

class Knight: public Unit{
public:
    Knight(int);
    ~Knight();
    bool valid_move(int posX,int posY);
    bool valid_attack(int posX,int posY);
    bool valid_pos(int posX,int posY);

};

#endif
