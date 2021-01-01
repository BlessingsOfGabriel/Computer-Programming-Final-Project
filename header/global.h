#ifndef GLOBAL_H
#define GLOBAL_H
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
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
    Pause,
    GameOver,
    Quit
};


enum ButtonType {
    Start, Tutorial, Option, Continue, Restart, Store, Status, Attack, Heal
};

enum UnitType {
    
};

/*enum ObstacleType {
    
};*/

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern ItemType itemName[12];
#endif
