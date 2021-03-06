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
std::pair<int, int> REGISTER(-1, -1);
std::pair<int, int> boardToAct(std::pair<int, int>);
void initialize();
void loadMedia();
void menu(SDL_Event& event);
void loading1(SDL_Event& event);
void loading2(SDL_Event& event);
void loading3(SDL_Event& event);
void loading4(SDL_Event& event);
void loading5(SDL_Event& event);
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
            case Loading_1: loading1(event); break;
			case Loading_2: loading2(event); break;
			case Loading_3: loading3(event); break;
			case Loading_4: loading4(event); break;
			case Loading_5: loading5(event); break;
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
	TTF_Init();
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
    GameOver1.loadTexture("GameOver1");
    GameOver2.loadTexture("GameOver2");
	gBoard.loadTexture("Board");
	Store.loadTexture("Store");
    loadedSound.playSound(4, "BGM", -1);
}

void menu(SDL_Event& event){
	while( SDL_PollEvent(&event) != 0 ){
		if(event.key.keysym.sym == SDLK_SPACE && event.key.type == SDL_KEYUP){
            gameState = Loading_1;
            break;
        }
        else if (event.type == SDL_QUIT) { gameState = Quit; break; }
        startButton->handleEvent(&event);
    }
    SDL_RenderClear( gRenderer);
	StartMenu.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    StartMenu.render(0, 0);
    SDL_RenderPresent( gRenderer );
}

void loading1(SDL_Event& event){
	while( SDL_PollEvent(&event) != 0 ) {
        if (event.key.keysym.sym == SDLK_RIGHT && event.key.type == SDL_KEYUP) {
            gameState = Loading_2;
            break;
        }
        else if (event.type == SDL_QUIT) { gameState = Quit; break; }
    }
    SDL_RenderClear( gRenderer );

	Load.loadTexture("Tutorial1");
    Load.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
	Load.render(0, 0);
    SDL_RenderPresent( gRenderer );
}

void loading2(SDL_Event& event){
	while( SDL_PollEvent(&event) != 0 ) {
        if (event.key.keysym.sym == SDLK_RIGHT && event.key.type == SDL_KEYUP) {
            gameState = Loading_3;
            break;
        }
		else if(event.key.keysym.sym == SDLK_LEFT && event.key.type == SDL_KEYUP){
			gameState = Loading_1;
			break;
		}
        else if (event.type == SDL_QUIT) { gameState = Quit; break; }
    }
    SDL_RenderClear( gRenderer );

	Load.loadTexture("Tutorial2");
	Load.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    Load.render(0, 0);
    SDL_RenderPresent( gRenderer );
}

void loading3(SDL_Event& event){
	while( SDL_PollEvent(&event) != 0 ) {
        if (event.key.keysym.sym == SDLK_RIGHT && event.key.type == SDL_KEYUP){
            gameState = Loading_4;
            break;
        }
		else if(event.key.keysym.sym == SDLK_LEFT && event.key.type == SDL_KEYUP){
			gameState = Loading_2;
			break;
		}
        else if (event.type == SDL_QUIT) { gameState = Quit; break; }
    }
    SDL_RenderClear( gRenderer );

	Load.loadTexture("Tutorial3");
	Load.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    Load.render(0, 0);
    SDL_RenderPresent( gRenderer );
}

void loading4(SDL_Event& event){
	while( SDL_PollEvent(&event) != 0 ) {
        if (event.key.keysym.sym == SDLK_RIGHT && event.key.type == SDL_KEYUP){
            gameState = Loading_5;
            break;
        }
		else if(event.key.keysym.sym == SDLK_LEFT && event.key.type == SDL_KEYUP){
			gameState = Loading_3;
			break;
		}
        else if (event.type == SDL_QUIT) { gameState = Quit; break; }
    }
    SDL_RenderClear( gRenderer );

	Load.loadTexture("Tutorial4");
	Load.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    Load.render(0, 0);
    SDL_RenderPresent( gRenderer );
}

void loading5(SDL_Event& event){
	while( SDL_PollEvent(&event) != 0 ) {
        if (event.key.keysym.sym == SDLK_SPACE && event.key.type == SDL_KEYUP){
            gameState = Playing_1;
            break;
        }
		else if(event.key.keysym.sym == SDLK_LEFT && event.key.type == SDL_KEYUP){
			gameState = Loading_4;
			break;
		}
        else if (event.type == SDL_QUIT) { gameState = Quit; break; }
    }
    SDL_RenderClear( gRenderer );

	Load.loadTexture("Tutorial5");
	Load.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    Load.render(0, 0);
    SDL_RenderPresent( gRenderer );
}

void playing1(SDL_Event& event){
	while(SDL_PollEvent(&event) != 0){
		if(event.type == SDL_QUIT) { gameState = Quit; break; }
        else if(gBoard.get_base0() <= 0 || gBoard.get_base1() <= 0) {
            gameState = GameOver;
            break;
		}
		if(event.key.keysym.sym == SDLK_e,event.key.type == SDL_KEYUP){
			REGISTER.first = -1;
			REGISTER.second = -1;
			gameState = Playing_2;
			break;
		}
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 20; j++){
				if(tiles[i][j] -> getTriggered()){
					if(REGISTER.first == -1 && REGISTER.second == -1){
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
				tiles[i][j] -> setTriggered(false);
			}
		}
		for(int i = 0; i < 20; i++)
			for(int j = 0; j < 20; j++)
				tiles[i][j] -> handleEvent(&event);
	}
	SDL_RenderClear( gRenderer );
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            tiles[i][j] -> resize(SCREEN_HEIGHT / 20, SCREEN_HEIGHT / 20);
            std::pair<int, int>actPos = boardToAct(std::pair<int, int>(i, j));
			tiles[i][j] -> setPos(actPos.first, actPos.second);
            tiles[i][j] -> render(actPos.first, actPos.second);
        }
    }
	gBoard.resize(SCREEN_HEIGHT, SCREEN_HEIGHT);
	gBoard.render((SCREEN_WIDTH - SCREEN_HEIGHT) / 2, 0);
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			std::pair<int, int> boardPos(i, j);
			gBoard.getUnit(i, j) -> resize(SCREEN_HEIGHT / 20, SCREEN_HEIGHT / 20);
			gBoard.getUnit(i, j) -> render(boardToAct(boardPos).first, boardToAct(boardPos).second);
		}
	}

	//Status1.update(SCREEN_WIDTH, SCREEN_HEIGHT);
	//Status2.update(SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_RenderPresent( gRenderer );
}

void playing2(SDL_Event& event){
	while(SDL_PollEvent(&event) != 0){
		if(event.type == SDL_QUIT) { gameState = Quit; break; }
        else if(gBoard.get_base0() <= 0 || gBoard.get_base1() <= 0) {
            gameState = GameOver;
            break;
		}
		if(event.key.keysym.sym == SDLK_e,event.key.type == SDL_KEYUP){
			REGISTER.first = -1;
			REGISTER.second = -1;
			gameState = Playing_1;
			break;
		}
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 20; j++){
				if(tiles[i][j] -> getTriggered()){
					if(REGISTER.first == -1 && REGISTER.second == -1){
                        if(gBoard.getUnit(i, j) -> getFaction() != 0){
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
				tiles[i][j] -> setTriggered(false);
			}
		}
		for(int i = 0; i < 20; i++)
			for(int j = 0; j < 20; j++)
				tiles[i][j] -> handleEvent(&event);
	}
	SDL_RenderClear( gRenderer );
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            tiles[i][j] -> resize(SCREEN_HEIGHT / 20, SCREEN_HEIGHT / 20);
            std::pair<int, int>actPos = boardToAct(std::pair<int, int>(i, j));
			tiles[i][j] -> setPos(actPos.first, actPos.second);
            tiles[i][j] -> render(actPos.first, actPos.second);
        }
    }
	gBoard.resize(SCREEN_HEIGHT, SCREEN_HEIGHT);
	gBoard.render((SCREEN_WIDTH - SCREEN_HEIGHT) / 2, 0);
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			std::pair<int, int> boardPos(i, j);
			gBoard.getUnit(i, j) -> resize(SCREEN_HEIGHT / 20, SCREEN_HEIGHT / 20);
			gBoard.getUnit(i, j) -> render(boardToAct(boardPos).first, boardToAct(boardPos).second);
		}
	}

	//Status1.update(SCREEN_WIDTH, SCREEN_HEIGHT);
	//Status2.update(SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_RenderPresent( gRenderer );
}

void gameover(SDL_Event& event){
	while( SDL_PollEvent(&event) != 0 ) {
        if (event.key.keysym.sym == SDLK_SPACE && event.key.type == SDL_KEYUP){
            gameState = Menu;
            break;
		}
        else if (event.type == SDL_QUIT) {
			gameState = Quit;
			break;
		}
    }
    SDL_RenderClear( gRenderer );

    if(gBoard.get_base1() == 0) {
		GameOver1.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
        GameOver1.render(0,0);
    }
    else {
		GameOver1.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
        GameOver2.render(0,0);
    }
    SDL_RenderPresent( gRenderer );
}

void store1(SDL_Event& event){
	while(SDL_PollEvent(&event) != 0 ){
		if(buy[0] -> getTriggered() && Status1.valid_buy(0)){
			Unit* a = new Soldier(0);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_1;
			tiles[REGISTER.first][REGISTER.second] -> setTriggered(false);
			REGISTER.first = -1;
			REGISTER.second = -1;
			buy[0] -> setTriggered(false);
			break;
		}
        if(buy[1] -> getTriggered() && Status1.valid_buy(1)){
			Unit* a = new Archer(0);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_1;
			tiles[REGISTER.first][REGISTER.second] -> setTriggered(false);
			REGISTER.first = -1;
			REGISTER.second = -1;
			buy[1] -> setTriggered(false);
			break;
		}
        if(buy[2] -> getTriggered() && Status1.valid_buy(2)){
			Unit* a = new Knight(0);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_1;
			tiles[REGISTER.first][REGISTER.second] -> setTriggered(false);
			REGISTER.first = -1;
			REGISTER.second = -1;
			buy[2] -> setTriggered(false);
			break;
		}
        if(buy[3] -> getTriggered() && Status1.valid_buy(3)){
			Unit* a = new Tower(0);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_1;
			tiles[REGISTER.first][REGISTER.second] -> setTriggered(false);
			REGISTER.first = -1;
			REGISTER.second = -1;
			buy[3] -> setTriggered(false);
			break;
		}
        if(buy[4] -> getTriggered() && Status1.valid_buy(4)){
			Unit* a = new GoldTower(0);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_1;
			tiles[REGISTER.first][REGISTER.second] -> setTriggered(false);
			REGISTER.first = -1;
			REGISTER.second = -1;
			buy[4] -> setTriggered(false);
			break;
		}
		for(int i = 0; i < 5; i++)
			buy[i] -> handleEvent(&event);
	}

    Store.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    Store.render(0, 0);
	for(int i = 0; i < 5; i++){
		buy[i] -> setPos(SCREEN_WIDTH * i / 5, SCREEN_HEIGHT * 3 / 4);
		buy[i] -> resize(SCREEN_WIDTH / 5, SCREEN_WIDTH / 10);
		buy[i] -> render(SCREEN_WIDTH * i / 5, SCREEN_HEIGHT * 3 / 4);
	}
    SDL_RenderPresent(gRenderer);
}

void store2(SDL_Event& event){
	while(SDL_PollEvent(&event) != 0 ){
		if(buy[0] -> getTriggered() && Status2.valid_buy(0)){
			Unit* a = new Soldier(1);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_2;
			tiles[REGISTER.first][REGISTER.second] -> setTriggered(false);
			REGISTER.first = -1;
			REGISTER.second = -1;
			buy[0] -> setTriggered(false);
			break;
		}
        if(buy[1] -> getTriggered() && Status2.valid_buy(1)){
			Unit* a = new Archer(1);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_2;
			tiles[REGISTER.first][REGISTER.second] -> setTriggered(false);
			REGISTER.first = -1;
			REGISTER.second = -1;
			buy[1] -> setTriggered(false);
			break;
		}
        if(buy[2] -> getTriggered() && Status2.valid_buy(2)){
			Unit* a = new Knight(1);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_2;
			tiles[REGISTER.first][REGISTER.second] -> setTriggered(false);
			REGISTER.first = -1;
			REGISTER.second = -1;
			buy[2] -> setTriggered(false);
			break;
		}
        if(buy[3] -> getTriggered() && Status2.valid_buy(3)){
			Unit* a = new Tower(1);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_2;
			tiles[REGISTER.first][REGISTER.second] -> setTriggered(false);
			REGISTER.first = -1;
			REGISTER.second = -1;
			buy[3] -> setTriggered(false);
			break;
		}
        if(buy[4] -> getTriggered() && Status2.valid_buy(4)){
			Unit* a = new GoldTower(1);
			gBoard.add_unit(REGISTER.first, REGISTER.second, a);
			gameState = Playing_2;
			tiles[REGISTER.first][REGISTER.second] -> setTriggered(false);
			REGISTER.first = -1;
			REGISTER.second = -1;
			buy[4] -> setTriggered(false);
			break;
		}
		for(int i = 0; i < 5; i++)
			buy[i] -> handleEvent(&event);
	}

    Store.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    Store.render(0, 0);
	for(int i = 0; i < 5; i++){
		buy[i] -> setPos(SCREEN_WIDTH * i / 5, SCREEN_HEIGHT * 3 / 4);
		buy[i] -> resize(SCREEN_WIDTH / 5, SCREEN_WIDTH / 10);
		buy[i] -> render(SCREEN_WIDTH * i / 5, SCREEN_HEIGHT * 3 / 4);
	}
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
	actPos.first = (SCREEN_WIDTH - SCREEN_HEIGHT) / 2 + SCREEN_HEIGHT * boardPos.second / 20;
	actPos.second = SCREEN_HEIGHT * boardPos.first / 20;
	return actPos;
}
