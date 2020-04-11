#include "solving.h"

const int chieu_rong = 320;
const int chieu_cao = 320;


SDL_Window* cua_so = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, chieu_rong, chieu_cao, SDL_WINDOW_SHOWN);

SDL_Renderer* render = SDL_CreateRenderer(cua_so, -1, SDL_RENDERER_ACCELERATED);
SDL_Texture* map1 = NULL;
SDL_Texture* gameoverimg = NULL;
SDL_Texture* win = NULL;

int Count = 0;
int Count1 = 0;
int x=-1, y=-1;
bool flag = false;
bool quit = false;
bool result = false;

int grid[12][12];
int sgrid[12][12];

bool isOpen[12][12];
bool isMark[12][12];

void openCell(int x, int y)
{
    if(isOpen[x][y] == true||isMark[x][y] == true)
        return ;
    isOpen[x][y] = true;
    if(grid[x][y] == 9)
        return ;
    Count1++;
    if(grid[x][y]>0&&grid[x][y]<10)
    {
        sgrid[x][y] = grid[x][y];
    }
    else if(grid[x][y]==0){
        sgrid[x][y]=0;
        int r1=x==1 ? 0:-1;
        int c1=y==1 ? 0:-1;
        int r2=x==10 ? 1:2;
        int c2=y==10 ? 1:2;
        for(;r1<r2;r1++){
            for(int j=c1;j<c2;j++){
                openCell(x+r1, y+j);
            }
        }
    }
    return ;
}


int main(int arc, char*argv[]){

	srand(time(0));
	for(int i=1;i<=10;i++)
    {
        for(int j=1;j<=10;j++){
            sgrid[i][j] = 10;
        }
    }
    for(int i=0;i<=11;i++)
    {
        for(int j=0;j<=11;j++){
            isMark[i][j] = false;
        }
    }
    isMark[0][0]=true;
    for(int i=0;i<=11;i++)
    {
        for(int j=0;j<=11;j++){
            isOpen[i][j] = false;
        }
    }

	map1 = LoadTexture("tiles.jpg");
	gameoverimg = LoadTexture("gameover1.jpg");
	win = LoadTexture("win.jpg");

    SDL_Rect toa_do;
    toa_do.x = 0;
    toa_do.y = 0;
    toa_do.w = 320;
    toa_do.h = 320;

    SDL_Event phim;
    bool gameover = false;

	for(int i=1;i<=10;i++)
	{
		for(int j=1;j<=10;j++){
			if(rand()%6==0)
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



	//SDL_RenderCopy(render, map2, NULL, &toa_do);

    while(!gameover){
        while(SDL_PollEvent(&phim) != 0){
			if(phim.type == SDL_MOUSEBUTTONDOWN){
				if(phim.button.button == SDL_BUTTON_LEFT){
					SDL_GetMouseState(&x, &y);
					x=x/32;
					y=y/32;
					//isMark[x+1][y+1] = false;
					//Count1++;
				}
				if(phim.button.button == SDL_BUTTON_RIGHT){
					SDL_GetMouseState(&x, &y);
					x=x/32;
					y=y/32;
					isMark[x+1][y+1] = true;
				}
			}
			if(grid[x+1][y+1]==9&&isMark[x+1][y+1]==false){
                gameover = true;
                result = false;
			}
        }
        for(int i=1;i<=10;i++){
            for(int j=1;j<=10;j++){
                SDL_Rect clip = {sgrid[i][j]*32,0,32,32};// vị trí để cắt ảnh kết quả
                SDL_Rect screen = {(i-1)*32,(j-1)*32,32,32};
                SDL_RenderCopy(render, map1, &clip, &screen);
            }
        }

        if(Count1==Count)
            {gameover=true;}
		//SDL_Rect position;
		if(isMark[x+1][y+1]==false){
            //position ={grid[x+1][y+1]*32,0,32,32};
            openCell(x+1, y+1);
            }
		else
        {
            sgrid[x+1][y+1] = 11;
        }

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
