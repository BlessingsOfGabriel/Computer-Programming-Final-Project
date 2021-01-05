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
