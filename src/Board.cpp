#include"Board.h"

Board::Board(){
	_current = new Unit*[20];
	for(int i = 0; i < 20; i++)
		uptr[i] = new Unit[20];
}

Board::~Board(){
	delete[][]_current;
}

Board::add_unit
