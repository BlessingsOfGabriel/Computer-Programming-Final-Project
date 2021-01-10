#ifndef STATUS_H
#define STATUS_H
#include "Obj.h"
#include "Unit.h"
#include "global.h"

class Status: public Obj{
public:
    Status(int);
    ~Status();
	int calculate_gpt();
	void turn_plus();
	void add_Unit(Unit);
	void delete_Unit(int,int);
	void minus_gold(int);
	bool valid_buy(UnitType);
    SDL_Renderer *surfaceRenderer = NULL;

    TTF_Font* gFont = TTF_OpenFont("arial.ttf",12);

    SDL_Texture *surfaceTexture;

    int sWidth,sHeight;

    void updateStatusString();

    void free();

    void updateStatusSurface();

protected:
	int _goldPerTurn;
	int _goldAmount;
	int _turn;
	std::vector<Unit> _unitList;
	int _baseHealth;
	int _statusFaction;
};
#endif
