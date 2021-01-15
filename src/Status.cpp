#include "Status.h"
#include "Obj.h"
#include "global.h"
#include <cmath>
#include<vector>
#include<string>

using namespace std;

Status::Status(int x){
    _statusFaction = x;
    _turn = 0;
    _goldPerTurn = 5;
    _goldAmount = 0;
    _baseHealth = 10;
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

bool Status::valid_buy(UnitType type){
    switch(type){
        case Soldier:{
            if(_goldAmount-2<0)
                return false;
            else
                return true;
            break;
        }
        case Archer:{
            if(_goldAmount-2<0)
                return false;
            else
                return true;
            break;
        }
        case Knight:{
            if(_goldAmount-4<0)
                return false;
            else
                return true;
            break;
        }
        case Tower:{
            if(_goldAmount-3<0)
                return false;
            else
                return true;
            break;
        }
        case GoldTower:{
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
