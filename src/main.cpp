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
Obj background, StartMenu, GameOver1, GameOver2;
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
	 while( SDL_PollEvent( &e ) != 0 ) {
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
    startButton->update();
    startButton->resize(300, 50);

    SDL_RenderPresent( gRenderer );
}

void loading(SDL_Event& event){
	while( SDL_PollEvent( &e ) != 0 ) {
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
        else if(status1._health == 0 || statu2._health == 0) {
            gameState = GameOver;
            break; 
		}
		Button *endTurn = Button(EndTurn);
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 20; j++){
				if(Button[i][j].getTriggered()){
					if(RESISTOR.first == -1, RESISTOR.second == -1){
						RESISTOR.first = i;
						RESISTOR.second = j;
					}
					else{
						if(board[RESISTOR.first][RESISTOR.second].valid_move()
					}
				}
			}
		}
	}
}

void playing2(SDL_Event& event){

}

void gameover(SDL_Event& event){

}

void store(SDL_Event& event){

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
