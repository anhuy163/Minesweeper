#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int chieu_rong = 320;
const int chieu_cao = 320;


SDL_Window* cua_so = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, chieu_rong, chieu_cao, SDL_WINDOW_SHOWN);

SDL_Renderer* render = SDL_CreateRenderer(cua_so, -1, SDL_RENDERER_ACCELERATED);


SDL_Texture* LoadTexture(std::string path){
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load(path.c_str());
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF ));
    texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    return texture;
}


int x=-1, y=-1;
bool flag = false;

int main(int arc, char*argv[]){

	srand(time(0));

	//SDL_Texture* man_hinh = LoadTexture("hinh_nen.png");
    SDL_Texture* map2 = LoadTexture("completed1.png");
	SDL_Texture* map1 = LoadTexture("tiles.jpg");

    SDL_Rect toa_do;
    toa_do.x = 0;
    toa_do.y = 0;
    toa_do.w = 320;
    toa_do.h = 320;

    SDL_Event phim;
    bool exit = false;

	int grid[12][12];
	int sgrid[12][12]; // để hiển thị
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
		}
	}



	SDL_RenderCopy(render, map2, NULL, &toa_do);

    while(!exit){
        while(SDL_PollEvent(&phim) != 0){
            if(phim.type == SDL_QUIT){
                exit = true;
            }
			if(phim.type == SDL_MOUSEBUTTONDOWN){
				if(phim.button.button == SDL_BUTTON_LEFT){
					SDL_GetMouseState(&x, &y);
					x=x/32;
					y=y/32;
					flag = false;
				}
				if(phim.button.button == SDL_BUTTON_RIGHT){
					SDL_GetMouseState(&x, &y);
					x=x/32;
					y=y/32;
					flag = true;
				}
			}
        }
        //SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
        //SDL_RenderClear(render);
		SDL_Rect position;//= {grid[x+1][y+1]*32,0,32,32};
		if(flag==false){
            position ={grid[x+1][y+1]*32,0,32,32};
		}
		else
        {
            position = {11*32,0,32,32};
        }
		SDL_Rect currentpos = {x*32,y*32,32,32};

		SDL_RenderCopy(render, map1, &position, &currentpos);
        //SDL_RenderCopy(render, map, NULL, &toa_do);
        SDL_RenderPresent(render);
    }


	return 0;
}
