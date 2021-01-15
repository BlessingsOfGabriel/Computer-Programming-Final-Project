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
	for(int i = 0; i < 20; i++){
		delete[] _current[i];
	}
	delete[] _current;
}

void Board::add_unit(int posX,int posY,Unit new_unit){
    if(new_unit.valid_pos(posX,posY))
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
    if(_current[x][y].valid_attack(_current[posX][posY]._xpos,_current[posX][posY]._ypos)){
        _current[posX][posY]._health -= _current[x][y]._damage;
        if(_current[posX][posY]._health>0)
            _current[posX][posY].deathchecker = 1;
        else{
            _current[posX][posY].deathchecker = 0;
            delete_unit(_current[posX][posY]._xpos,_current[posX][posY]._ypos);
        }

    }
}

Unit& Board::getUnit(int x,int y){
    return _current[x][y];
}
