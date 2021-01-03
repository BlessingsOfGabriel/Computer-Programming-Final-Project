#include "Obj.h"
#include<iostream>
#include<string>
using namespace std;

Obj::Obj(){};

Obj::~Obj(){};

int Obj::getHeight(){
    return _height;
}

int Obj::getWidth(){
    return _width;
}

void Obj::resize(int newHeight,int newWidth){
    _height = newHeight;
    _width = newWidth;
}

void free(){};

