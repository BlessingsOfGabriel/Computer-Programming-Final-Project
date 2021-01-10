#include "Archer.h"
#include "Unit.h"
#include "Obj.h"
#include<cmath>
#include<string>

using namespace std;

Archer::Archer(int faction):Unit(faction){
    _health = 2;
    _damage = 2;
    _move = 1;
    _name = "Archer";
}

Archer::~Archer(){}

bool Archer::valid_move(int posX,int posY){
    if((abs(posX-_xpos)+abs(posY-_ypos))<=_move)
        return true;
    else
        return false;
}

bool Archer::valid_attack(int posX,int posY){
    if(abs(posX-_xpos)==0 && abs(posY-_ypos)<=3 )
        return true;
    else if(abs(posX-_xpos)<=3 && abs(posY-_ypos)==0)
        return true;
    else if(abs(posX-_xpos)==1 && abs(posY-_ypos)==1)
        return true;
    else if(abs(posX-_xpos)==2 && abs(posY-_ypos)==2)
        return true;
    else if(abs(posX-_xpos)==3 && abs(posY-_ypos)==3)
        return true;
    else
        return false;
}

bool Archer::valid_pos(int posX,int posY){
    if(_faction == 0){
        if(posX>posY){
            _xpos = posX;
            _ypos = posY;
            return true;
        }
        else
            return false;
    }
    else if(_faction == 1){
        if(posX<posY){
            _xpos = posX;
            _ypos = posY;
            return true;
        }
        else
            return false;
    }
}
