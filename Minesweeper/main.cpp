#include"texture.h"
#include"datasolving.h"
#include<ctime>

const int chieu_rong = 320;
const int chieu_cao = 320;
SDL_Window* cua_so = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, chieu_rong, chieu_cao, SDL_WINDOW_SHOWN);
SDL_Renderer* render = SDL_CreateRenderer(cua_so, -1, SDL_RENDERER_ACCELERATED);
extern texture Game_map;


int main(int arc, char*argv[]){
    srand(time(0));
    Game_play();
}
