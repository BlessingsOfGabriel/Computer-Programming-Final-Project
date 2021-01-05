#include "Status.h"
#include "Obj.h"
#include <iostream>
#include <cmath>
#include<vector>

using namespace std;

int Status::calculate_gpt(){
    _goldPerTurn = 5;
    _goldAmount = round(_goldPerTurn + (_gold_amount + _goldPerTurn)*0.2);

    return _gold_amount;
}

void Status::add_Unit(Unit unit){
    _unitList.push_back(unit);
}

void Status::delete_Unit(int x,int y){
    vector<Unit>::iterator it;
    for(it=begin ; it!=end ; it++){
        if(*it._xPos==x && *it._yPos==y)
            _unitList.erase(it);
    }
}
