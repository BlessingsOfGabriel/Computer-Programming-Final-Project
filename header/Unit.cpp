#include "Obj.h"
#include "Unit.h"
#include<cmath>

using namespace std;

Unit::Unit(){};

Unit::~Unit(){};

void Unit::heal(){};

bool Unit::valid_move(int posX,int posY){
    if((abs(posX-_xPos)+abs(posY-_yPos))<=_max_move)
        return true;
    else
        return false;
}

void Unit::move(int posX,int posY){
    if(valid_move(posX,posY)){
        _xPos = posX;
        _yPos = posY;
    }
}

bool Unit::valid_attack(int posX,int posY){
    return true;
}

void Unit::attack(Unit &target){
    if(valid_attack(target._xPos,target._yPos)){
        target._health -= _damage;

    }
}



