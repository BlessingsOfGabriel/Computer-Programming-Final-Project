#include "Soldier.h"
#include "Unit.h"
#include "Obj.h"
#include<cmath>
#include<string>

using namespace std;

Soldier::Soldier(int faction):Unit(faction){
    _health = 3;
    _damage = 1;
    _move = 2;
    _name = "Soldier";
}

Soldier::~Soldier(){}

bool Soldier::valid_move(int posX,int posY){
    if((abs(posX-_xpos)+abs(posY-_ypos))<=_move)
        return true;
    else
        return false;
}

bool Soldier::valid_attack(int posX,int posY){
    if(abs(posX-_xpos)<=1 && abs(posY-_ypos)<=1)
        return true;
    else
        return false;
}

bool Soldier::valid_pos(int posX,int posY){
    if(_faction == 1){
        if(posX>posY){
            _xpos = posX;
            _ypos = posY;
            return true;
        }
        else
            return false;
    }
    else if(_faction == 0){
        if(posX<posY){
            _xpos = posX;
            _ypos = posY;
            return true;
        }
        else
            return false;
    }
}
