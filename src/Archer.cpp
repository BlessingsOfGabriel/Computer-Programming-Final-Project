#include "Archer.h"
#include "Unit.h"
#include "Obj.h"
#include<cmath>

using namespace std;

Archer::Archer(int fraction):Unit(fraction){
    _health = 2;
    _damage = 2;
    _move = 1;
}

Archer::~Archer(){}

bool Archer::valid_move(int posX,int posY){
    if((abs(posX-_xPos)+abs(posY-_yPos))<=_move)
        return true;
    else
        return false;
}

bool Archer::valid_attack(int posX,int posY){
    if(abs(posX-_xPos)==0 && abs(posY-_yPos)<=3 )
        return true;
    else if(abs(posX-_xPos)<=3 && abs(posY-_yPos)==0)
        return true;
    else if(abs(posX-_xPos)==1 && abs(posY-_yPos)==1)
        return true;
    else if(abs(posX-_xPos)==2 && abs(posY-_yPos)==2)
        return true;
    else if(abs(posX-_xPos)==3 && abs(posY-_yPos)==3)
        return true;
    else
        return false;
}

bool Archer::valid_pos(int posX,int posY){
    if(_fraction == 0){
        if(posX>posY){
            _xPos = posX;
            _yPos = posY;
            return true;
        }
        else
            return false;
    }
    else if(_fraction == 1){
        if(posX<posY){
            _xPos = posX;
            _yPos = posY;
            return true;
        }
        else
            return false;
    }
}
