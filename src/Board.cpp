#include"Board.h"
#include "Obj.h"
#include "Unit.h"

using namespace std;

Board::Board(){
	_current = new Unit*[20];
	for(int i = 0; i < 20; i++)
        _current[i] = new Unit[20];
    _base0 = 10;
    _base1 = 10;
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
    if(((posX==0&&(posY==17||posY==18||posY==19)) || ((posX==1)&&(posY==17||posY==18||posY==19)) ||(posX==2&&(posY==17||posY==18||posY==19))) && _current[x][y]._faction == 0){
        if(_current[x][y].valid_attack(_posX,_posY))
            _base1 -= _current[x][y]._damage;
    }
    else if(((posY==0&&(posX==17||posY==19||posY==19)) || (posY==1&&(posX==17||posY==19||posY==19)) || (posY==2&&(posX==17||posY==19||posY==19))) && _current[x][y]._faction == 1){
        if(_current[x][y].valid_attack(_posX,_posY))
            _base0 -= _current[x][y]._damage;
    }

    else{
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
}

Unit& Board::getUnit(int x,int y){
    return _current[x][y];
}

int Board::get_base0(){
    return _base0;
}

int Board::get_base1(){
    return _base1;
}
