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
Button* endTurn;
Button* tiles[20][20];
Button* buy[5];
Board gBoard;
Status Status1, Status2;
Obj StartMenu, Load, Store, GameOver1, GameOver2;
pair<int, int> REGISTER;
pair<int, int> boardToAct(pair<int, int>);

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
			case Store_1: store1(event); break;
            case Store_2: store2(event); break;
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
    endTurnButton = new Button(EndTurn);
    restartButton = new Button(Restart);
    for(int i = 0; i < 5; i++)
        buy[i] = new Button(Buy);
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 20; j++)
            tiles[i][j] = new Button(Common);

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
			gameState = playing_2;
			break;
		}
		
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 20; j++){
				if(tiles[i][j] -> getTriggered()){
					if(REGISTER.first == -1, REGISTER.second == -1){
                        if(gBoard.getUnit(i, j).getFaction() != 1){
						    REGISTER.first = i;
						    REGISTER.second = j;
                        }
						if(Board[i][j].getFaction == -1){
							gameState = store1;
							break;
						}
						else
							break;
					}
					else{
						if(board[REGISTER.first][REGISTER.second].valid_move(i, j)){
							pair<int, int> newPos = boardToAct(pair<int, int>(i, j));
							gBoard.getUnit(REGISTER.first, REGISTER.second).render(newPos.first, newPos.second);
							SDL_RenderPresent(gRenderer);
							gBoard.move(REGISTER.first, REGISTER.second);
							break;
						}
						else if(board[REGISTER.first][REGISTER.second].valid_attack(i, j)){
							gBoard[REGISTER.first][REGISTER.second].attack(gBoard[i][j]);
							break;
						}
					}
				}
			}
		}
	}
    SDL_SetRenderDrawColor( gRenderer, 182, 196, 182, 0 );
    SDL_RenderClear( gRenderer );

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            tiles[i][j] -> resize(60, 60);
            pair<int, int>actPos = boardToAct(pair<int, int>(i, j));
            tiles[i][j] -> render(actPos.first, actPos.second);
        }
    }
	gBoard.resize(1200, 1200);
	gBoard.render(400, 0);
	SDL_RenderPresent( gRenderer );
}

void playing2(SDL_Event& event){
	while(SDL_PollEvent(&event) != 0){
		if(e.type == SDL_QUIT) { gameState = Quit; break; }
        else if(status1._baseHealth == 0 || statu2._baseHealth == 0) {
            gameState = GameOver;
            break; 
		}
		if(endTurn->get_triggered()){
			endTurn->set_triggered(false);
			gameState = playing_1;
			break;
		}
		
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 20; j++){
				if(tiles[i][j] -> getTriggered()){
					if(REGISTER.first == -1, REGISTER.second == -1){
                        if(gBoard.getUnit(i, j).getFaction() != 0){
						    REGISTER.first = i;
						    REGISTER.second = j;
                        }
						if(Board[i][j].getFaction == -1){
							gameState = Store_2;
							break;
						}
						else
							break;
					}
					else{
						if(board[REGISTER.first][REGISTER.second].valid_move(i, j)){
							pair<int, int> newPos = boardToAct(pair<int, int>(i, j));
							gBoard.getUnit(REGISTER.first, REGISTER.second).render(newPos.first, newPos.second);
							SDL_RenderPresent(gRenderer);
							gBoard.move(REGISTER.first, REGISTER.second);
							break;
						}
						else if(board[REGISTER.first][REGISTER.second].valid_attack(i, j)){
							gBoard[REGISTER.first][REGISTER.second].attack(gBoard[i][j]);
							break;
						}
					}
				}
			}
		}
	}
	SDL_SetRenderDrawColor( gRenderer, 182, 196, 182, 0 );
    SDL_RenderClear( gRenderer );

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            tiles[i][j] -> resize(60, 60);
            pair<int, int>actPos = boardToAct(pair<int, int>(i, j));
            tiles[i][j] -> render(actPos.first, actPos.second);
        }
    }
	gBoard.resize(1200, 1200);
	gBoard.render(400, 0);
	SDL_RenderPresent( gRenderer );
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

    if(status2._baseHealth == 0) {
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
			Board.add_Unit(REGISTER.first, REGISTER.second, new Soldier(0));
			gameState = playing1;
			buy[0] -> set_triggered(false);
			break;
		}
        if(buy[1] -> getTriggered()){
			Board.add_Unit(REGISTER.first, REGISTER.second, new Archer(0));
			gameState = playing1;
			buy[1] -> set_triggered(false);
			break;
		}
        if(buy[2] -> getTriggered()){
			Board.add_Unit(REGISTER.first, REGISTER.second, new Knight(0));
			gameState = playing1;
			buy[2] -> set_triggered(false);
			break;
		}
        if(buy[3] -> getTriggered()){
			Board.add_Unit(REGISTER.first, REGISTER.second, new Tower(0));
			gameState = playing1;
			buy[3] -> set_triggered(false);
			break;
		}
        if(buy[4] -> getTriggered()){
			Board.add_Unit(REGISTER.first, REGISTER.second, new GoldTower(0));
			gameState = playing1;
			buy[4] -> set_triggered(false);
			break;
		}
	}
    gStore.resize(2000, 1200);
    gStore.render(0, 0)
    
    SDL_RenderPresent(gRenderer);
}

void store2(SDL_Event& event){
	while( SDL_PollEvent(&event) != 0 ){
		if(buy[0] -> getTriggered()){
			Board.add_Unit(REGISTER.first, REGISTER.second, new Soldier(1));
			gameState = playing1;
			buy[0] -> set_triggered(false);
			break;
		}
        if(buy[1] -> getTriggered()){
			Board.add_Unit(REGISTER.first, REGISTER.second, new Archer(1));
			gameState = playing1;
			buy[1] -> set_triggered(false);
			break;
		}
        if(buy[2] -> getTriggered()){
			Board.add_Unit(REGISTER.first, REGISTER.second, new Knight(1));
			gameState = playing1;
			buy[2] -> set_triggered(false);
			break;
		}
        if(buy[3] -> getTriggered()){
			Board.add_Unit(REGISTER.first, REGISTER.second, new Tower(1));
			gameState = playing1;
			buy[3] -> set_triggered(false);
			break;
		}
        if(buy[4] -> getTriggered()){
			Board.add_Unit(REGISTER.first, REGISTER.second, new GoldTower(1));
			gameState = playing1;
			buy[4] -> set_triggered(false);
			break;
		}
	}

    gStore.resize(2000, 1200);
    gStore.render(0, 0)
    
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
