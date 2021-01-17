#ifndef STATUS_H
#define STATUS_H
#include "Obj.h"
#include "Unit.h"
#include "global.h"
#include "Board.h"

class Status: public Obj{
public:
    Status(int);
    ~Status();
	int calculate_gpt(int, int);
	void turn_plus();
	void add_Unit(Unit, int, int);
	void delete_Unit(int,int, int, int);
	void minus_gold(int, int, int);
	bool valid_buy(int);
    SDL_Renderer *surfaceRenderer = NULL;

    TTF_Font* gFont = TTF_OpenFont("arial.ttf",12);

    SDL_Texture *surfaceTexture;

    int sWidth,sHeight;

    void updateStatusString();

    void free();

    void updateStatusSurface(int, int);
    void update(int, int);

protected:
	int _goldPerTurn;
	int _goldAmount;
	int _turn;
	std::vector<Unit> _unitList;
	int _statusFaction;
	std::string _statusString;
};
#endif
