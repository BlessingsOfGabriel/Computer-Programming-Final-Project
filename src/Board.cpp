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
    _current[posX][posY] = nullptr;
}
