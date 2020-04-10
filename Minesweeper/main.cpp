#include "solving.h"

const int chieu_rong = 320;
const int chieu_cao = 320;


SDL_Window* cua_so = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, chieu_rong, chieu_cao, SDL_WINDOW_SHOWN);

SDL_Renderer* render = SDL_CreateRenderer(cua_so, -1, SDL_RENDERER_ACCELERATED);
SDL_Texture* map2 = NULL;
SDL_Texture* map1 = NULL;
SDL_Texture* gameoverimg = NULL;
SDL_Texture* win = NULL;

int Count = 0;
int Count1 = 0;
int x=-1, y=-1;
bool flag = false;
bool quit = false;
bool result = false;


int main(int arc, char*argv[]){

	srand(time(0));

	//SDL_Texture* man_hinh = LoadTexture("hinh_nen.png");
    map2 = LoadTexture("completed1.png");
	map1 = LoadTexture("tiles.jpg");
	gameoverimg = LoadTexture("lose.png");
	win = LoadTexture("win.jpg");

    SDL_Rect toa_do;
    toa_do.x = 0;
    toa_do.y = 0;
    toa_do.w = 320;
    toa_do.h = 320;

    SDL_Event phim;
    bool gameover = false;

	int grid[12][12];
	for(int i=1;i<=10;i++)
	{
		for(int j=1;j<=10;j++){
			if(rand()%5==0)
				grid[i][j]=9;
			else
				grid[i][j]=0;
		}
	}
	for(int i=1;i<=10;i++){
		for(int j=1;j<=10;j++){
			int n=0;
			if(grid[i][j]==9) continue;
			if(grid[i][j+1]==9) n++;
			if(grid[i-1][j]==9) n++;
			if(grid[i][j-1]==9) n++;
			if(grid[i-1][j-1]==9) n++;
			if(grid[i+1][j+1]==9) n++;
			if(grid[i-1][j+1]==9) n++;
			if(grid[i+1][j-1]==9) n++;
			if(grid[i+1][j]==9) n++;
		    grid[i][j]=n;
		    Count++;
		}
	}



	SDL_RenderCopy(render, map2, NULL, &toa_do);

    while(!gameover){
        while(SDL_PollEvent(&phim) != 0){
			if(phim.type == SDL_MOUSEBUTTONDOWN){
				if(phim.button.button == SDL_BUTTON_LEFT){
					SDL_GetMouseState(&x, &y);
					x=x/32;
					y=y/32;
					flag = false;
					Count1++;
				}
				if(phim.button.button == SDL_BUTTON_RIGHT){
					SDL_GetMouseState(&x, &y);
					x=x/32;
					y=y/32;
					flag = true;
				}
			}
			if(grid[x+1][y+1]==9&&flag==false){
                gameover = true;
                result = false;
			}
        }
        if(Count1==Count)
            gameover=true;

		SDL_Rect position;// vị trí để cắt ảnh kết quả
		if(flag==false){
            position ={grid[x+1][y+1]*32,0,32,32};

		}
		else
        {
            position = {11*32,0,32,32};
        }
		SDL_Rect currentpos = {x*32,y*32,32,32};// vị trí để tải ảnh đã cắt lên

		SDL_RenderCopy(render, map1, &position, &currentpos);
        SDL_RenderPresent(render);
    }
    SDL_Rect position1;
    SDL_Rect currentpos1;
    SDL_RenderClear(render);
    for(int i=1;i<=10;i++){
        for(int j=1;j<=10;j++){
            position1 = {grid[i][j]*32,0,32,32};
            currentpos1 = {(i-1)*32,(j-1)*32,32,32};
            SDL_RenderCopy(render, map1, &position1, &currentpos1);
            SDL_RenderPresent(render);
        }
    }
    SDL_Delay(1000);
    if(Count1==Count){
        result = true;
    }
    if(result==true){
        SDL_RenderCopy(render, win, NULL, &toa_do);
        SDL_RenderPresent(render);
    }
    else if(result==false){
        SDL_RenderCopy(render, gameoverimg, NULL, &toa_do);
        SDL_RenderPresent(render);
    }
    while(!quit){
        while(SDL_PollEvent(&phim)!=0)
        {
            if(phim.type == SDL_QUIT){
               quit = true;
        }
        }
    }
    close();
	return 0;
}
