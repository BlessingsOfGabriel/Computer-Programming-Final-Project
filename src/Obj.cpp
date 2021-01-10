#include "Obj.h"
#include<iostream>
#include<string>
using namespace std;

Obj::Obj(): _width(0), _height(0), _texture(NULL), _xPos(0), _yPos(0) {}

Obj::~Obj() {
	free();
}

void Obj::loadTexture(std::string name) {
    free();
    _texture = loadedTexture.getTexture(name);
    SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height);
}

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

void Obj::free() {
	if (_texture != NULL) {
		_texture = NULL;
		_width = 0;
		_height = 0;
	}
}

void Obj::render(int posX,int posY){
	SDL_Rect srcRect(_xPos, _yPos, _width, _height);
	SDL_Rect DestRect(posX, posY, _width, _height);
	SDL_RenderCopy(gRenderer, _texture, &srcRect, &DestRect);
}
