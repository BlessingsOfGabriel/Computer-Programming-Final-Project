#include"Board.h"
#include "Obj.h"
#include "Unit.h"

using namespace std;

Board::Board(){
	_current = new Unit*[20];
	for(int i = 0; i < 20; i++)
        _current[i] = new Unit[20];
}

Board::~Board(){
	delete[][]_current;
}

void Board::add_unit(int posX,int posY,Unit new_unit){
    _current[posX][posY] = new_unit;
}

void Board::delete_unit(int posX,int posY){
    _current[posX][posY]._faction = -1;
}

void Board::move(int posX,int posY){
    if(valid_move(posX,posY)){
        _xpos = posX;
        _ypos = posY;
    }
}

void Board::attack(Unit &target){
    if(valid_attack(target._xpos,target._ypos)){
        target.attacked(_damage);
    }
}

void Board::attacked(int damage)
{
    _health -= damage;
    if(_health>0)
        deathchecker = 1;
    else
        deathchecker = 0;
}
