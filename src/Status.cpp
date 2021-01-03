#include "Status.h"
#include "Obj.h"
#include <iostream>
#include <cmath>

using namespace std;

int Status::calculate_gpt(){
    _goldPerTurn = 5;
    _goldAmount = round(_goldPerTurn + (_gold_amount + _goldPerTurn)*0.2);

    return _gold_amount;
}
