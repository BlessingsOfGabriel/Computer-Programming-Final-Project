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

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
int SCREEN_WIDTH = 1200;
int SCREEN_HEIGHT = 800;
int LEVEL_WIDTH = 2000;
int LEVEL_HEIGHT = 2000;
GameState gameState;
Button* startButton;
Button* restartButton;
Button* tiles[20][20];
Obj StartMenu, Load, GameOver1, GameOver2;
pair<int, int> RESISTOR;
pair<double, double> boardToAct(pair<int, int>);

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
            case Playing_1: playing_1(event); break;
			case Playing_2: playing_2(event); break;
			case Store: store(event); break;
            case GameOver: gameover(event); break;
            default: gameState = Quit; break;
        }
    }
	close();
}

void initialize(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
		throw SDL_GetError();
    if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )) 
		printf( "Warning: Linear texture filtering not enabled!" );
    gWindow = SDL_CreateWindow( "ConquEEr", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE );
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
	buyButton = new Button(Buy);
    restartButton = new Button(Restart);

    StartMenu.loadTexture("StartMenu");
    loadingmenu.loadTexture("loadingmenu");
    GameOver1.loadTexture("GameOver1");
    GameOver2.loadTexture("GameOver2");
    loadedSound.playSound(4, "BGM", -1);
}

void menu(SDL_Event& event){
	 while( SDL_PollEvent(&event) != 0 ) {
        if (startButton->get_triggered() == true) {
            gameState = Loading;
            startButton->set_triggered(false);
            break;
        }
        else if (e.type == SDL_QUIT) { gameState = Quit; break; }
        startButton->handleEvent(&e);
    }
    SDL_SetRenderDrawColor( gRenderer, 182, 196, 182, 0 );
    SDL_RenderClear( gRenderer );

    background.resize(LEVEL_WIDTH, LEVEL_HEIGHT);
    background.render(0, 0);
    StartMenu.render(0, 0);
    StartMenu.resize(1200, 800);
    startButton->resize(300, 50);

    SDL_RenderPresent( gRenderer );
}

void loading(SDL_Event& event){
	while( SDL_PollEvent(&event) != 0 ) {
        if (e.key.keysym.sym == SDLK_SPACE) {
            gameState = playing1;
            break;
        }
        else if (e.type == SDL_QUIT) { gameState = Quit; break; }
    }
    SDL_SetRenderDrawColor( gRenderer, 182, 196, 182, 0 );
    SDL_RenderClear( gRenderer );

    loadingmenu.render(0, 0);
    loadingmenu.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent( gRenderer );
}

void playing1(SDL_Event& event){
	while(SDL_PollEvent(&event) != 0){
		if(e.type == SDL_QUIT) { gameState = Quit; break; }
        else if(status1._baseHealth == 0 || statu2._baseHealth == 0) {
            gameState = GameOver;
            break; 
		}
		Button *endTurn = Button(EndTurn);
		if(endTurn->get_triggered()){
			endTurn->set_triggered(false);
			gameState = playing2;
			break;
		}
		
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 20; j++){
				if(Button[i][j].getTriggered()){
					if(RESISTOR.first == -1, RESISTOR.second == -1){
						RESISTOR.first = i;
						RESISTOR.second = j;
						if(Board[i][j].getFaction == -1){
							gameState = store;
							break;
						}
						else
							break;
					}
					else{
						if(board[RESISTOR.first][RESISTOR.second].valid_move(i, j)){
							board[RESISTOR.first][RESISTOR.second].move(i, j);
							pair<double, double> newPos = boardToAct(pair<int, int>(i, j));
							board[RESISTOR.first][RESISTOR.second].render(newPos.first, newPos.second);
							break;
						}
						else if(board[RESISTOR.first][RESISTOR.second].valid_attack(i, j)){
							board[RESISTOR.first][RESISTOR.second].attack(board[i][j]);
							break;
						}
					}
				}
			}
		}
	}
	SDL_RenderPresent( gRenderer );
}

void playing2(SDL_Event& event){
	while(SDL_PollEvent(&event) != 0){
		if(e.type == SDL_QUIT) { gameState = Quit; break; }
        else if(status1._baseHealth == 0 || statu2._baseHealth == 0) {
            gameState = GameOver;
            break; 
		}
		Button *endTurn = Button(EndTurn);
		if(endTurn->get_triggered()){
			endTurn->set_triggered(false);
			gameState = playing1;
			break;
		}
		
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 20; j++){
				if(Button[i][j].getTriggered()){
					if(RESISTOR.first == -1, RESISTOR.second == -1){
						RESISTOR.first = i;
						RESISTOR.second = j;
						if(Board[i][j].getFaction == -1){
							gameState = store1;
							break;
						}
						else
							break;
					}
					else{
						if(board[RESISTOR.first][RESISTOR.second].valid_move(i, j)){
							board[RESISTOR.first][RESISTOR.second].move(i, j);
							pair<double, double> newPos = boardToAct(pair<int, int>(i, j));
							board[RESISTOR.first][RESISTOR.second].render(newPos.first, newPos.second);
							break;
						}
						else if(board[RESISTOR.first][RESISTOR.second].valid_attack(i, j)){
							board[RESISTOR.first][RESISTOR.second].attack(board[i][j]);
							break;
						}
					}
				}
			}
		}
	}
	SDL_RenderPresent(gRenderer);
}


void gameover(SDL_Event& event){
	while( SDL_PollEvent( &e ) != 0 ) {
        if (restartButton->get_triggered() == true) {
            gameState = Loading;
            restartButton->set_triggered(false);
            loadedSound.playSound(4, "BGM", -1);
            break; 
		}
        else if (e.type == SDL_QUIT) { 
			gameState = Quit; 
			break; 
		}
        restartButton->handleEvent(&e);
        if (e.type == SDL_QUIT) { 
			gameState = Quit; 
			break; 
		}
    }
    SDL_SetRenderDrawColor( gRenderer, 182, 196, 182, 0 );
    SDL_RenderClear( gRenderer );

    if() {
        GameOver1.render(0,0);
        GameOver1.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    else {
        GameOver2.render(0,0);
        GameOver2.resize(SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    restartButton->update();
    restartButton->resize(350, 70);

    SDL_RenderPresent( gRenderer );
}

void store1(SDL_Event& event){
	while( SDL_PollEvent(&event) != 0 ){
		if(buyButton[0].getTriggered()){
			Board.add_Unit(Soldier(0));
			gameState = playing1;
			buyButton[0].set_triggered(false);
			break;
		}
        if(buyButton[1].getTriggered()){
			Board.add_Unit(Archer(0));
			gameState = playing1;
			buyButton[0].set_triggered(false);
			break;
		}
        if(buyButton[2].getTriggered()){
			Board.add_Unit(Knight(0));
			gameState = playing1;
			buyButton[0].set_triggered(false);
			break;
		}
        if(buyButton[3].getTriggered()){
			Board.add_Unit(Tower(0));
			gameState = playing1;
			buyButton[0].set_triggered(false);
			break;
		}
        if(buyButton[4].getTriggered()){
			Board.add_Unit(Goldtower(0));
			gameState = playing1;
			buyButton[0].set_triggered(false);
			break;
		}
	}
    SDL_RenderPresent(gRenderer);
}

void store2(SDL_Event& event){
	while( SDL_PollEvent(&event) != 0 ){
		if(buyButton[0].getTriggered()){
			Board.add_Unit(Soldier(1));
			gameState = playing1;
			buyButton[0].set_triggered(false);
			break;
		}
        if(buyButton[1].getTriggered()){
			Board.add_Unit(Archer(1));
			gameState = playing1;
			buyButton[0].set_triggered(false);
			break;
		}
        if(buyButton[2].getTriggered()){
			Board.add_Unit(Knight(1));
			gameState = playing1;
			buyButton[0].set_triggered(false);
			break;
		}
        if(buyButton[3].getTriggered()){
			Board.add_Unit(Tower(1));
			gameState = playing1;
			buyButton[0].set_triggered(false);
			break;
		}
        if(buyButton[4].getTriggered()){
			Board.add_Unit(Goldtower(1));
			gameState = playing1;
			buyButton[0].set_triggered(false);
			break;
		}
	}
    SDL_RenderPresent(gRenderer);
}

void close() {
	background.free();
    StartMenu.free();
    loadingmenu.free();


    loadedTexture.free();

    loadedSound.free();
    startButton = NULL;
    continueButton = NULL;
    restartButton = NULL;
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}
