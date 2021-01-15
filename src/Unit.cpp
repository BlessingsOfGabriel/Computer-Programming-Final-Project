#include "Obj.h"
#include "Unit.h"
#include<cmath>

using namespace std;

Unit::Unit(int faction){
    _faction = faction;
    deathchecker = 1;
}

Unit::~Unit(){}

void Unit::heal(){}

bool Unit::valid_move(int posX,int posY){
    return false;
}

bool Unit::valid_attack(int posX,int posY){
    return false;
}

bool Unit::valid_pos(int posX,int posY){
    return true;
}

void updatePersonality()
{
    personality = _name + " (" + to_string(posX) + "," + to_string(posY) + ")   ATK: " + to_string(_damage) + "  HP: " + to_string(_health);
}

