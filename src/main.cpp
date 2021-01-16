#include "global.h"
#include "Obj.h"
#include "LoadMedia.h"
#include "Archer.h"
#include "Board.h"
#include "Button.h"
#include "GoldTower.h"
#include "Knight.h"
#include "Soldier.h"
#include "Status.h"
#include "Tower.h"
#include "Unit.h"
#include <iostream>

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
int SCREEN_WIDTH = 2000;
int SCREEN_HEIGHT = 1200;
GameState gameState;
Button* startButton;
Button* restartButton;
Button* endTurnButton;
Button* tiles[20][20];
Button* buy[5];
Board gBoard;
Status Status1(0), Status2(1);
Obj StartMenu, Load, Store, GameOver1, GameOver2;
std::pair<int, int> REGISTER;
std::pair<int, int> boardToAct(std::pair<int, int>);
void initialize();
void loadMedia();
void menu(SDL_Event& event);
void loading(SDL_Event& event);
void playing1(SDL_Event& event);
void playing2(SDL_Event& event);
void gameover(SDL_Event& event);
void store1(SDL_Event& event);
void store2(SDL_Event& event);
void close();


int main(int argc, char* argv[]){
	try {
        initialize();
        loadMedia();
    }
    catch (const char* message) {
        printf("Error: %s\n", message);
    }

	SDL_Event event;
	gameState = Menu;

	while (gameState != Quit) {
        SDL_GetWindowSize(gWindow, &SCREEN_WIDTH, &SCREEN_HEIGHT);
        switch (gameState) {
            case Menu: menu(event); break;
            case Loading: loading(event); break;
            case Playing_1: playing1(event); break;
			case Playing_2: playing2(event); break;
			case Store_1: store1(event); break;
            case Store_2: store2(event); break;
            case GameOver: gameover(event); break;
            default: gameState = Quit; break;
        }
    }
	close();
	return 0;
}

void initialize(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
		throw SDL_GetError();
    if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ))
		printf( "Warning: Linear texture filtering not enabled!" );
    gWindow = SDL_CreateWindow( "ConquEEror", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE );
    if (gWindow == NULL)
		throw SDL_GetError();
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if (gRenderer == NULL)
		throw SDL_GetError();
    SDL_SetRenderDrawColor( gRenderer, 182, 196, 182, 100 );
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init( imgFlags ) & imgFlags))
		throw IMG_GetError();
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
		throw Mix_GetError();
}

void loadMedia(){
    loadedTexture.loadAllTexture();
    loadedSound.loadAllSound();

    startButton = new Button(Start);
    endTurnButton = new Button(EndTurn);
    restartButton = new Button(Restart);
    for(int i = 0; i < 5; i++)
        buy[i] = new Button(Buy);
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 20; j++)
            tiles[i][j] = new Button(Common);

    StartMenu.loadTexture("StartMenu");
    Load.loadTexture("LoadingMenu");
    GameOver1.loadTexture("GameOver1");
    GameOver2.loadTexture("GameOver2");
    loadedSound.playSound(4, "BGM", -1);
}

void menu(SDL_Event& event){
	while( SDL_PollEvent(&event) != 0 ) {
        if (startButton->getTriggered() == true) {
            gameState = Loading;
            startButton->setTriggered(false);
            break;
        }
        else if (event.type == SDL_QUIT) { gameState = Quit; break; }
        startButton->handleEvent(&event);
    }
    SDL_RenderClear( gRenderer);
	StartMenu.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    StartMenu.render(0, 0);
	startButton -> setPos(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT * 3 / 4);
	startButton -> render(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT * 3 / 4);
    SDL_RenderPresent( gRenderer );
}

void loading(SDL_Event& event){
	while( SDL_PollEvent(&event) != 0 ) {
        if (event.key.keysym.sym == SDLK_SPACE) {
            gameState = Playing_1;
            break;
        }
        else if (event.type == SDL_QUIT) { gameState = Quit; break; }
    }
    SDL_SetRenderDrawColor( gRenderer, 182, 196, 182, 0 );
    SDL_RenderClear( gRenderer );

    Load.render(0, 0);
    Load.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent( gRenderer );
}

void playing1(SDL_Event& event){
	while(SDL_PollEvent(&event) != 0){
		if(event.type == SDL_QUIT) { gameState = Quit; break; }
        else if(gBoard.get_base0() <= 0 || gBoard.get_base1() <= 0) {
            gameState = GameOver;
            break;
		}
		if(endTurnButton->getTriggered()){
			endTurnButton->setTriggered(false);
			REGISTER.first = -1;
			REGISTER.second = -1;
			gameState = Playing_2;
			break;
		}
		endTurnButton -> handleEvent(&event);
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 20; j++){
				if(tiles[i][j] -> getTriggered()){
					if(REGISTER.first == -1, REGISTER.second == -1){
                        if(gBoard.getUnit(i, j) -> getFaction() != 1){
						    REGISTER.first = i;
						    REGISTER.second = j;
                        }
						if(gBoard.getUnit(i, j) -> getFaction() == -1){
							gameState = Store_1;
							break;
						}
						else
							break;
					}
					else{
						if(gBoard.getUnit(REGISTER.first, REGISTER.second) -> valid_move(i, j)){
							std::pair<int, int> newPos = boardToAct(std::pair<int, int>(i, j));
							gBoard.getUnit(REGISTER.first, REGISTER.second) -> render(newPos.first, newPos.second);
							gBoard.move(REGISTER.first, REGISTER.second, i, j);
							break;
						}
						else if(gBoard.getUnit(REGISTER.first, REGISTER.second) -> valid_attack(i, j)){
							gBoard.attack(REGISTER.first, REGISTER.second, i, j);
							break;
						}
					}
				}
				tiles[i][j] -> handleEvent(&event);
			}
		}
	}

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            tiles[i][j] -> resize(60, 60);
            std::pair<int, int>actPos = boardToAct(std::pair<int, int>(i, j));
            tiles[i][j] -> render(actPos.first, actPos.second);
        }
    }
	gBoard.resize(1200, 1200);
	gBoard.render(400, 0);
	SDL_RenderPresent( gRenderer );
}

void playing2(SDL_Event& event){
	while(SDL_PollEvent(&event) != 0){
		if(event.type == SDL_QUIT) { gameState = Quit; break; }
        else if(gBoard.get_base0() <= 0 || gBoard.get_base1() <= 0) {
            gameState = GameOver;
            break;
		}
		if(endTurnButton->getTriggered()){
			endTurnButton->setTriggered(false);
			REGISTER.first = -1;
			REGISTER.second = -1;
			gameState = Playing_1;
			break;
		}
		endTurnButton -> handleEvent(&event);

		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 20; j++){
				if(tiles[i][j] -> getTriggered()){
					if(REGISTER.first == -1, REGISTER.second == -1){
                        if(gBoard.getUnit(i, j) -> getFaction() != 0){
						    REGISTER.first = i;
						    REGISTER.second = j;
                        }
						if(gBoard.getUnit(i, j) -> getFaction() == -1){
							gameState = Store_2;
							break;
						}
						else
							break;
					}
					else{
						if(gBoard.getUnit(REGISTER.first, REGISTER.second) -> valid_move(i, j)){
							std::pair<int, int> newPos = boardToAct(std::pair<int, int>(i, j));
							gBoard.getUnit(REGISTER.first, REGISTER.second) -> render(newPos.first, newPos.second);
							gBoard.move(REGISTER.first, REGISTER.second, i, j);
							break;
						}
						else if(gBoard.getUnit(REGISTER.first, REGISTER.second) -> valid_attack(i, j)){
							gBoard.attack(REGISTER.first, REGISTER.second, i, j);
							break;
						}
					}
				}
				tiles[i][j] -> handleEvent(&event);
			}
		}
	}

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            tiles[i][j] -> resize(60, 60);
            std::pair<int, int>actPos = boardToAct(std::pair<int, int>(i, j));
            tiles[i][j] -> render(actPos.first, actPos.second);
        }
    }
	gBoard.resize(1200, 1200);
	gBoard.render(400, 0);
	SDL_RenderPresent( gRenderer );
}

void gameover(SDL_Event& event){
	while( SDL_PollEvent(&event) != 0 ) {
        if (restartButton->getTriggered() == true) {
            gameState = Loading;
            restartButton->setTriggered(false);
            loadedSound.playSound(4, "BGM", -1);
            break;
		}
        else if (event.type == SDL_QUIT) {
			gameState = Quit;
			break;
		}
        restartButton->handleEvent(&event);
        if (event.type == SDL_QUIT) {
			gameState = Quit;
			break;
		}
    }
    SDL_SetRenderDrawColor( gRenderer, 182, 196, 182, 0 );
    SDL_RenderClear( gRenderer );

    if(gBoard.get_base1() == 0) {
        GameOver1.render(0,0);
        GameOver1.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    else {
        GameOver2.render(0,0);
        GameOver2.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    restartButton -> resize(350, 70);
    restartButton -> render(825, 1000);
    SDL_RenderPresent( gRenderer );
}

void store1(SDL_Event& event){
	while( SDL_PollEvent(&event) != 0 ){
		if(buy[0] -> getTriggered()){
			Unit* a = new Soldier(0);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_1;
			buy[0] -> setTriggered(false);
			break;
		}
        if(buy[1] -> getTriggered()){
			Unit* a = new Archer(0);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_1;
			buy[1] -> setTriggered(false);
			break;
		}
        if(buy[2] -> getTriggered()){
			Unit* a = new Knight(0);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_1;
			buy[2] -> setTriggered(false);
			break;
		}
        if(buy[3] -> getTriggered()){
			Unit* a = new Tower(0);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_1;
			buy[3] -> setTriggered(false);
			break;
		}
        if(buy[4] -> getTriggered()){
			Unit* a = new GoldTower(0);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_1;
			buy[4] -> setTriggered(false);
			break;
		}
	}
    Store.resize(2000, 1200);
    Store.render(0, 0);

    SDL_RenderPresent(gRenderer);
}

void store2(SDL_Event& event){
	while( SDL_PollEvent(&event) != 0 ){
		if(buy[0] -> getTriggered()){
			Unit* a = new Soldier(1);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_2;
			buy[0] -> setTriggered(false);
			break;
		}
        if(buy[1] -> getTriggered()){
			Unit* a = new Archer(1);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_2;
			buy[1] -> setTriggered(false);
			break;
		}
        if(buy[2] -> getTriggered()){
			Unit* a = new Knight(1);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_2;
			buy[2] -> setTriggered(false);
			break;
		}
        if(buy[3] -> getTriggered()){
			Unit* a = new Tower(1);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_2;
			buy[3] -> setTriggered(false);
			break;
		}
        if(buy[4] -> getTriggered()){
			Unit* a = new GoldTower(1);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_2;
			buy[4] -> setTriggered(false);
			break;
		}
	}

    Store.resize(2000, 1200);
    Store.render(0, 0);

    SDL_RenderPresent(gRenderer);
}

void close() {
    StartMenu.free();
    Load.free();
    loadedTexture.free();
    loadedSound.free();
    startButton = NULL;
    endTurnButton = NULL;
    restartButton = NULL;
	for(int i = 0; i < 5; i++){
		buy[i] = NULL;
	}
	for(int i = 0; i < 20; i++)
		for(int j = 0; j < 20; j++)
			tiles[i][j] = NULL;
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

std::pair<int, int> boardToAct(std::pair<int, int> boardPos){
	std::pair<int, int> actPos;
	actPos.first = boardPos.second * 60 + 400;
	actPos.second = boardPos.first * 60;
	return actPos;
}
