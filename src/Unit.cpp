#include "Obj.h"
#include "Unit.h"
#include<cmath>

using namespace std;

Unit::Unit(int faction){
    _faction = faction;
}

Unit::~Unit(){};

void Unit::heal(){};

bool Unit::valid_move(int posX,int posY){
    return false;
}

void Unit::move(int posX,int posY){
    if(valid_move(posX,posY)){
        _xpos = posX;
        _ypos = posY;
    }
}

bool Unit::valid_attack(int posX,int posY){
    return false;
}

void Unit::attack(Unit &target){
    if(valid_attack(target._xpos,target._ypos)){
        target._health -= _damage;
    }
}

bool Unit::valid_pos(int posX,int posY){
    return true;
}


