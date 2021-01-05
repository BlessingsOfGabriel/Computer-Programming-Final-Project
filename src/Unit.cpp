#include "Obj.h"
#include "Unit.h"
#include<cmath>

using namespace std;

<<<<<<< HEAD
Unit::Unit(int faction){
    _faction = faction;
=======
Unit::Unit(){
	
>>>>>>> d25a2d5d57b7df39e410b6bd367afc6cb75fc7cf
};

Unit::~Unit(){};

void Unit::heal(){};

bool Unit::valid_move(int posX,int posY){
    return false;
}

void Unit::move(int posX,int posY){
    if(valid_move(posX,posY)){
        _xPos = posX;
        _yPos = posY;
    }
}

bool Unit::valid_attack(int posX,int posY){
    return false;
}

void Unit::attack(Unit &target){
    if(valid_attack(target._xPos,target._yPos)){
        target._health -= _damage;
    }
}

bool Unit::valid_pos(int posX,int posY){
    return false;
}


