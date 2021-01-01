#include "Soldier.h"
#include "Unit.h"
#include "Obj.h"
#include<cmath>

using namespace std;

Soldier::Soldier(){
    _health = 3;
    _damage = 1;
    _move = 2;
}

Soldier::~Soldier(){}

bool Soldier::valid_move(int posX,int posY){
    if((abs(posX-_xPos)+abs(posY-_yPos))<=_move)
        return true;
    else
        return false;
}

bool Soldier::valid_attack(int posX,int posY){
    if(abs(posX-_xPos)<=1 && abs(posY-_yPos)<=1)
        return true;
    else
        return false;
}
