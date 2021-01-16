#include "Button.h"
#include "global.h"

std::string typeToString(ButtonType _type){
	switch(_type){
		case Start:
			return "Start";
			break;
		case Restart:
			return "Restart";
			break;
		case Buy:
			return "Buy";
			break;
		case EndTurn:
			return "EndTurn";
			break;
		case Common:
			return "Common";
			break;
		default:
			return "Unknown";
			break;
	}
}
Button::Button(ButtonType _type): Obj(), triggered(false) {
    //Initialize
    _buttonType = _type;
    loadTexture(typeToString(_buttonType));
}

Button::~Button() {
    free();
    triggered = false;
}

void Button::setPos(int x, int y) {
    _xPos = x;
    _yPos = y;
}

void Button::handleEvent(SDL_Event *event) {
	if( event -> type == SDL_MOUSEMOTION || event -> type == SDL_MOUSEBUTTONDOWN || event -> type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is outside of the button
		if( x < _xPos || x > _xPos + _width || y < _yPos || y > _yPos + _height){ inside = false; }

		//Mouse is inside button
		if( inside && event -> type == SDL_MOUSEBUTTONDOWN) { 
            triggered = true; 
        }
	}
}

void Button::setTriggered(bool state) {
    triggered = state;
}
bool Button::getTriggered() {
    return triggered;
}

/*void Button::update() {
    switch(_buttonType) {
        case Start: 
			setPos((SCREEN_WIDTH - getWidth())/ 2, SCREEN_HEIGHT * 2 / 3); 
			break;
        case Restart: 
			setPos((SCREEN_WIDTH - getWidth())/ 2, SCREEN_HEIGHT * 2 / 3); 
			break;
		case 
        default: 
			setPos(0, 0); 
			break;
    }
    render(_posX, _posY);
}*/
