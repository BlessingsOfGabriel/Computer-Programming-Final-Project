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
    if(new_unit.valid_pos)
        _current[posX][posY] = new_unit;
}

void Board::delete_unit(int posX,int posY){
    _current[posX][posY]._faction = -1;
}

void Board::move(int x,int y,int posX,int posY){
    if(_current[x][y].valid_move(posX,posY)){
        _current[x][y]._xpos = posX;
        _current[x][y]._ypos = posY;
    }
}

void Board::attack(int x,int y,int posX,int posY){
    if(_current[x][y].valid_attack(_current[x][y]._xpos,_current[x][y]._ypos)){
        _current[x][y]._health -= damage;
        if(_current[x][y]._health>0)
            _current[x][y].deathchecker = 1;
        else{
            _current[x][y].deathchecker = 0;
            _current[x][y].delete_unit(_current[x][y]._xpos,_current[x][y]._ypos);
        }

    }
}

Unit& Board::getUnit(int x,int y){
    return _current[x][y];
}
