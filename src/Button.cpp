#include "Button.h"
#include "global.h"

Button::Button(ButtonType _type): Obj(), triggered(false) {
    //Initialize
    _buttonType = _type;
    loadTexture(typeToString(_buttonType));
};

Button::~Button() {
    free();
    triggered = false;
}

void Button::setPos(int x, int y) {
    _posX = x;
    _posY = y;
}

void Button::handleEvent(SDL_Event *e) {
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is outside of the button
		if( x < _posX || x > _posX + _objWidth || y < _posY || y > _posY + _objHeight){ inside = false; }

		//Mouse is inside button
		if( inside && e->type == SDL_MOUSEBUTTONDOWN) { 
            triggered = true; 
        }
	}
}

void Button::set_triggered(bool state) {
    triggered = state;
}
bool Button::get_triggered() {
    return triggered;
}
