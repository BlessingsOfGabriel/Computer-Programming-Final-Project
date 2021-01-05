#include "Status.h"
#include "Obj.h"
#include <cmath>
#include<vector>

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
        if(*it._xPos==x && *it._yPos==y)
            _unitList.erase(it);
    }
}
