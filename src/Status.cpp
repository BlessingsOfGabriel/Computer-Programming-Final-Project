#include "Status.h"
#include "Obj.h"
#include "global.h"
#include <cmath>
#include<vector>
#include<string>

using namespace std;

Status::Status(){
    _turn = 0;
    _goldPerTurn = 5;
    _goldAmount = 0;
}

Status::~Status(){};

void Status::turn_plus(){
    _turn++;
}

int Status::calculate_gpt(){
    _goldAmount = round(_goldPerTurn + (_goldAmount + _goldPerTurn)*0.2);
    return _goldAmount;
}

void Status::add_Unit(Unit unit){
    _unitList.push_back(unit);
}

void Status::delete_Unit(int x,int y){
    vector<Unit>::iterator it;
    for(it=_unitList.begin(); it!=_unitList.end() ; it++){
        if(*it._xpos==x && *it._ypos==y)
            _unitList.erase(it);
    }
}

void Status::minus_gold(int x){
    _goldAmount -= x;
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
        statusString += it.personality;
        statusString += "\n";
    }
}

void surface::free()
{
	//Free texture if it exists
	if( surfaceTexture != NULL )
	{
		SDL_DestroyTexture( surfaceTexture );
		surfaceTexture = NULL;
		sWidth = 0;
		sHeight = 0;
	}
}
void status::updateStatusSurface()
{
    SDL_Color White = {255,255,255};
    free();
    statusRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    statusSurface = TTF_RenderText_Solid( gFont, statusString.c_str(), White );
    surfaceTexture = SDL_CreateTextureFromSurface(surfaceRenderer, statusSurface);
    sWidth = statusSurface->w;
    sHeight = statusSurface->h;
    SDL_FreeSurface(statusSurface);
    SDL_Rect renderQuad = (==) ?{0,0, 200,1600  }:{1800,0,200,1600};
    SDL_RenderCopy( surfaceRenderer, surfaceTexture, NULL, &renderQuad );
    SDL_RenderPresent(surfaceRenderer);
}
