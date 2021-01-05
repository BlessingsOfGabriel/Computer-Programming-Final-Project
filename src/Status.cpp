#include "Status.h"
#include "Obj.h"
#include "global.h"
#include <cmath>
#include<vector>
#include<string>

using namespace std;

Status::Status(){
    _turn = 0;
    _goldPerTurn = 5;
    _goldAmount = 0;
}

Status::~Status(){};

void Status::turn_plus(){
    _turn++;
}

int Status::calculate_gpt(){
    _goldAmount = round(_goldPerTurn + (_goldAmount + _goldPerTurn)*0.2);
    return _goldAmount;
}

void Status::add_Unit(Unit unit){
    _unitList.push_back(unit);
}

void Status::delete_Unit(int x,int y){
    vector<Unit>::iterator it;
    for(it=_unitList.begin(); it!=_unitList.end() ; it++){
        if(*it._xpos==x && *it._ypos==y)
            _unitList.erase(it);
    }
}

void Status::minus_gold(int x){
    _goldAmount -= x;
}

bool Status::valid_buy(UnitType type){
    switch(type){
        case(Soldier):{
            if(_goldAmount-2<0)
                return false;
            else
                return true;
            break;
        }
        case(Archer):{
            if(_goldAmount-2<0)
                return false;
            else
                return true;
            break;
        }
        case(Knight):{
            if(_goldAmount-4<0)
                return false;
            else
                return true;
            break;
        }
        case(Tower):{
            if(_goldAmount-3<0)
                return false;
            else
                return true;
            break;
        }
        case(GoldTower):{
            if(_goldAmount-5<0)
                return false;
            else
                return true;
            break;
        }
        default:
            return false;
            break;
    }
}
