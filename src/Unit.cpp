#include "Obj.h"
#include "Unit.h"
#include<cmath>

using namespace std;

Unit::Unit(int faction){
    _faction = faction;
    deathchecker = 1;
}

Unit::~Unit(){}

void Unit::heal(){}

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
        target.attacked(_damage);
    }
}

bool Unit::valid_pos(int posX,int posY){
    return true;
}

void Unit::attacked(int damage)
{
    _health -= damage;
    if(_health>0)
        deathchecker = 1;
    else
        deathchecker = 0;
}

