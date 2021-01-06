#include "Knight.h"
#include "Unit.h"
#include "Obj.h"
#include<cmath>
#include<string>

using namespace std;

Knight::Knight(int faction):Unit(faction){
    _health = 4;
    _damage = 2;
    _move = 2;
    _name = "Knight";
}

Knight::~Knight(){}

bool Knight::valid_move(int posX,int posY){
    if((abs(posX-_xpos)+abs(posY-_ypos))<=_move)
        return true;
    else
        return false;
}

bool Knight::valid_attack(int posX,int posY){
    if(abs(posX-_xpos)<=1 && abs(posY-_ypos)<=1)
        return true;
    else
        return false;
}

bool Knight::valid_pos(int posX,int posY){
    if(_fraction == 0){
        if(posX>posY){
            _xpos = posX;
            _ypos = posY;
            return true;
        }
        else
            return false;
    }
    else if(_fraction == 1){
        if(posX<posY){
            _xpos = posX;
            _ypos = posY;
            return true;
        }
        else
            return false;
    }
}
