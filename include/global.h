#ifndef GLOBAL_H
#define GLOBAL_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <map>
#include <time.h>

enum GameState {
    Menu,
    Loading,
    Playing,
    Store,
    GameOver,
    Quit
};


enum ButtonType {
    Start, Restart, Buy, EndTurn, Common
};

enum UnitType {
    Soldier, Archer, Knight, Tower, GoldTower
};

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
#endif
