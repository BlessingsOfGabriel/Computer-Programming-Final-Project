#include "global.h"
#include "main.h"
#include "Obj.h"
#include "LoadMedia.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
int SCREEN_WIDTH = 1200;
int SCREEN_HEIGHT = 800;
int LEVEL_WIDTH = 2000;
int LEVEL_HEIGHT = 2000;
GameState gameState;
Button* button(Start);
pair<int, int> RESISTOR;
pair<double, double> boardToAct(pair<int, int>);

int main(int argc, char* argv[]){
	initialize();
	loadMedia();
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
	
}

void loadMedia(){
	
}

void menu(SDL_Event& event){
			
}

void loading(SDL_Event& event){

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
						if(board[RESISTOR.first][RESISTOR.second].valid_move(int posX,int posY)
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

}
