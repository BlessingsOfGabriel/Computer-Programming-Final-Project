#include "Knight.h"
#include "Unit.h"
#include "Obj.h"
#include<cmath>

using namespace std;

Knight::Knight(){
    _health = 4;
    _damage = 2;
    _move = 2;
}

Knight::~Knight(){}

bool Knight::valid_move(int posX,int posY){
    if((abs(posX-_xPos)+abs(posY-_yPos))<=_move)
        return true;
    else
        return false;
}

bool Knight::valid_attack(int posX,int posY){
    if(abs(posX-_xPos)<=1 && abs(posY-_yPos)<=1)
        return true;
    else
        return false;
}
