#include "GoldTower.h"
#include "Unit.h"
#include "Obj.h"
#include<string>

using namespace std;

GoldTower::GoldTower(int faction):Unit(faction){
    _health = 1;
    _move = 0;
    _damage = 0;
    _name = "GoldTower";
}

GoldTower::~GoldTower(){}

bool GoldTower::valid_move(int posX,int posY){
    return false;
}

bool GoldTower::valid_attack(int posX,int posY){
    return false;
}

bool GoldTower::valid_pos(int posX,int posY){
    if(_fraction == 1){
        if(posX>posY){
            _xpos = posX;
            _ypos = posY;
            return true;
        }
        else
            return false;
    }
    else if(_fraction == 0){
        if(posX<posY){
            _xpos = posX;
            _ypos = posY;
            return true;
        }
        else
            return false;
    }
}
