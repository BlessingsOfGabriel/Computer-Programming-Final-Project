#include "GoldTower.h"
#include "Unit.h"
#include "Obj.h"

using namespace std;

GoldTower::GoldTower(){
    _health = 1;
}

GoldTower::~GoldTower(){}

bool GoldTower:valid_move(int posX,int posY){
    return false;
}

bool GoldTower:valid_attack(int posX,int posY){
    return false;
}

bool GoldTower:valid_pos(int posX,int posY){
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
