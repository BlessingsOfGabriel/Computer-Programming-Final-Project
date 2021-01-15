#include "Tower.h"
#include "Unit.h"
#include "Obj.h"
#include <cmath>
#include <string>

using namespace std;

Tower::Tower(int faction):Unit(faction){
    _health = 3;
    _damage = 1;
    _name = "Tower";
}

Tower::~Tower(){}

bool Tower::valid_attack(int posX,int posY){
    if(abs(posX-_xpos)<=1 && abs(posY-_ypos)<=1)
        return true;
    else
        return false;
}

bool Tower::valid_pos(int posX,int posY){
    if(_faction == 1){
        if(posX>=(posY+9)){
            _xpos = posX;
            _ypos = posY;
            return true;
        }
        else
            return false;
    }
    else if(_faction == 0){
        if((posX+9)<=posY){
            _xpos = posX;
            _ypos = posY;
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

bool Tower::valid_move(int posX,int posY){
    return false;
}

