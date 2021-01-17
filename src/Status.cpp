#include "Status.h"
#include "Obj.h"
#include "Unit.h"
#include "global.h"
#include "Board.h"
#include <cmath>
#include <vector>
#include <string>

using namespace std;

Status::Status(int x){
    _statusFaction = x;
    _turn = 0;
    _goldPerTurn = 5;
    _goldAmount = 0;
}

Status::~Status(){}

void Status::turn_plus(){
    _turn++;
}

int Status::calculate_gpt(int width, int height){
    _goldAmount = round(_goldPerTurn + (_goldAmount + _goldPerTurn)*0.2);
    return _goldAmount;
    update(width, height);
}

void Status::add_Unit(Unit unit, int width, int height){
    _unitList.push_back(unit);
    update(width, height);
}

void Status::delete_Unit(int x,int y, int width, int height){
    vector<Unit>::iterator it;
    for(it=_unitList.begin(); it!=_unitList.end() ; it++){
        if(it -> _xpos==x && it -> _ypos==y)
            _unitList.erase(it);
    }
    update(width, height);
}

void Status::minus_gold(int x, int width, int height){
    _goldAmount -= x;
    update(width, height);
}

bool Status::valid_buy(int x){
    switch(x){
        case 0:{
            if(_goldAmount-2<0)
                return false;
            else
                return true;
            break;
        }
        case 1:{
            if(_goldAmount-2<0)
                return false;
            else
                return true;
            break;
        }
        case 2:{
            if(_goldAmount-4<0)
                return false;
            else
                return true;
            break;
        }
        case 3:{
            if(_goldAmount-3<0)
                return false;
            else
                return true;
            break;
        }
        case 4:{
            if(_goldAmount-5<0)
                return false;
            else
                return true;
            break;
        }
        default:
            return false;
            break;
    }
}

void Status::updateStatusString()
{
    _statusString = "";
    vector<Unit>::iterator it;
    for(it=_unitList.begin(); it!=_unitList.end() ; it++){
        _statusString += it -> personality;
        _statusString += "\n";
    }
    _statusString += "GoldAmounts: ";
    _statusString += to_string(_goldAmount);
    _statusString += "\n";
    if(_statusFaction == 1)
        _statusString += to_string(gBoard.get_base1());
    else if(_statusFaction == 0)
        _statusString += to_string(gBoard.get_base0());
}

void Status::free()
{
	//Free texture if it exists
	if( surfaceTexture != NULL )
	{
		SDL_DestroyTexture( surfaceTexture );
		surfaceTexture = NULL;

	}
}
void Status::updateStatusSurface(int width, int height)
{
    SDL_Color White = {255,255,255};
    free();
    SDL_Renderer *statusRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    SDL_Surface *statusSurface = TTF_RenderText_Solid( gFont, _statusString.c_str(), White );
    SDL_Texture *surfaceTexture = SDL_CreateTextureFromSurface(statusRenderer, statusSurface);
    SDL_FreeSurface(statusSurface);
    SDL_Rect renderQuad;
    if(_statusFaction == 0)
    {
        renderQuad = {0, 0, (width - height) / 2, height};
    }
    else
    {
        renderQuad = {(width + height) / 2, 0, (width - height) / 2, height};
    }
    SDL_RenderCopy(statusRenderer, surfaceTexture, NULL, &renderQuad );
    system("PAUSE");
    SDL_RenderPresent(statusRenderer);
}

void Status::update(int width, int height){
    updateStatusString();
    updateStatusSurface(width, height);
}
