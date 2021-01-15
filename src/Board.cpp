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
        target._health -= damage;
        if(target._health>0)
            target.deathchecker = 1;
        else{
            target.deathchecker = 0;
            delete_unit(target._xpos,target._ypos);
        }

    }
}

