#include "Tower.h"
#include "Unit.h"
#include "Obj.h"
#include <cmath>

using namespace std;

Tower::Tower{}{
    _health = 3;
    _damage = 1;
}

Tower::~Tower(){}

bool Tower::valid_attack(int posX,int posY){
    if(abs(posX-_xPos)<=1 && abs(posY-_yPos)<=1)
        return true;
    else
        return false;
}

bool Tower::valid_pos(int posX,int posY){
    if(_fraction == 0){
        if(posX>=(posY+9)){
            _xPos = posX;
            _yPos = posY;
            return true;
        }
        else
            return false;
    }
    else if(_fraction == 1){
        if((posX+9)<=posY){
            _xPos = posX;
            _yPos = posY;
            return true;
        }
        else
            return false;
    }
}

bool Tower::valid_move(int posX,int posY){
    return false;
}

