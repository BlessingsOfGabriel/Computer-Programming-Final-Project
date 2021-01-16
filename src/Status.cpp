#include "Status.h"
#include "Obj.h"
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

int Status::calculate_gpt(){
    _goldAmount = round(_goldPerTurn + (_goldAmount + _goldPerTurn)*0.2);
    return _goldAmount;
    update();
}

void Status::add_Unit(Unit unit){
    _unitList.push_back(unit);
    update();
}

void Status::delete_Unit(int x,int y){
    vector<Unit>::iterator it;
    for(it=_unitList.begin(); it!=_unitList.end() ; it++){
        if(*it._xpos==x && *it._ypos==y)
            _unitList.erase(it);
    }
    update();
}

void Status::minus_gold(int x){
    _goldAmount -= x;
    update();
}

bool Status::valid_buy(int x){
    switch(type){
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

void status::updateStatusString()
{
    statusString = "";
    vector<Unit>::iterator it;
    for(it=_unitList.begin(); it!=_unitList.end() ; it++){
        statusString += *it.personality;
        statusString += "\n";
    }
    statusString += "GoldAmounts: ";
    statusString += to_string(_goldAmount);
    statusString += "\n";
    if(_statusFaction == 1)
        statusString += to_string(_base1);
    else if(_statusFaction == 0)
        statusFaction += to_string(_base0);
}

void status::free()
{
	//Free texture if it exists
	if( surfaceTexture != NULL )
	{
		SDL_DestroyTexture( surfaceTexture );
		surfaceTexture = NULL;

	}
}
void status::updateStatusSurface()
{
    SDL_Color White = {255,255,255};
    free();
    statusRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    statusSurface = TTF_RenderText_Solid( gFont, statusString.c_str(), White );
    surfaceTexture = SDL_CreateTextureFromSurface(statusRenderer, statusSurface);
    SDL_FreeSurface(statusSurface);
    SDL_Rect renderQuad = (_statusFaction == 0) ?{0,0, 200,1600}:{1800,0,200,1600};
    SDL_RenderCopy( surfaceRenderer, surfaceTexture, NULL, &renderQuad );
    SDL_RenderPresent(surfaceRenderer);
}

void status::update(){
    updateStatusString();
    updateStatusSurface();
}
