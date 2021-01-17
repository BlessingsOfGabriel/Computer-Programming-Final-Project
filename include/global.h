#ifndef GLOBAL_H
#define GLOBAL_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <time.h>

enum GameState {
    Menu,
    Loading_1,
    Loading_2,
    Loading_3,
    Loading_4,
    Loading_5,
    Playing_1,
    Playing_2,
    Store_1,
    Store_2,
    GameOver,
    Quit
};


enum ButtonType {
    Start, Restart, Buy, EndTurn, Common
};

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
#endif
