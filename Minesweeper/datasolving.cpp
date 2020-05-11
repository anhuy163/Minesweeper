#include "datasolving.h"
#include "texture.h"

using namespace std;

extern SDL_Renderer* render;
extern texture Game_map;
int grid[10][10];
int sgrid[10][10];
int safe_cell=0, opened_cell=0;

int dem_bom(int x, int y){
    int dem=0;
    int r1=(x==0) ? 0:-1; //int x=a==b ? c:d;
    int c1=(y==0) ? 0:-1;
    int r2=(x==9) ? 1:2;
    int c2=(y==9) ? 1:2;
    for(;r1<r2;r1++){
        for(int j=c1;j<c2;j++){
            if(grid[x+r1][y+j]==9){
                dem++;
            }
        }
    }
    return dem;
}
void Game_preparation(){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(rand()%5==0){
                grid[i][j]=9;
            }
            else
                safe_cell++;
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(grid[i][j]!=9){
                grid[i][j]=dem_bom(i, j);
            }
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            sgrid[i][j]=10;
        }
    }
}
void Open_cell(int x, int y){
    if(sgrid[x][y]>=0&&sgrid[x][y]<9)
        return;
    if(sgrid[x][y]==11)
        return;
    if(grid[x][y]==9)
        return;
    opened_cell++;
    if(grid[x][y]>=1&&grid[x][y]<9){
        sgrid[x][y]=grid[x][y];
    }
    else{
        if(grid[x][y]==0){
            sgrid[x][y]=0;
            int r1=(x==0) ? 0:-1;
            int c1=(y==0) ? 0:-1;
            int r2=(x==9) ? 1:2;
            int c2=(y==9) ? 1:2;
            for(;r1<r2;r1++){
                for(int j=c1;j<c2;j++){
                    Open_cell(x+r1, y+j);
                }
            }
        }
    }

}
int Game_play(){

    Game_preparation();
    int x=-1, y=-1;
    bool result=false;
    bool gameover=false;
    bool ketqua=false;
    SDL_Event phim;
    Game_map.Load_from_file("tiles.jpg");
    Game_map.Set_size(32, 32);
    while(!gameover){
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                Game_map.Set_rect(sgrid[i][j]*32, 0, 32, 32); // cat anh in ra map
                Game_map.Set_pos(i*32, j*32); // lay vi tri in ra man hinh
                Game_map.Render();
            }
        }
        SDL_RenderPresent(render);

        while(SDL_PollEvent(&phim)!=0){
            if(phim.type == SDL_QUIT)
            {
                return 0;
            }
            if(phim.type==SDL_MOUSEBUTTONDOWN){
                if(phim.button.button==SDL_BUTTON_LEFT){
                    SDL_GetMouseState(&x, &y);
                    x=x/32;
                    y=y/32;
                    if(grid[x][y]==9&&sgrid[x][y]!=11){
                        gameover=true;
                        result=false;
                    }
                    Open_cell(x, y);
                }
                if(phim.button.button==SDL_BUTTON_RIGHT){
                    SDL_GetMouseState(&x, &y);
                    x=x/32;
                    y=y/32;
                    if(sgrid[x][y]==11){
                        sgrid[x][y]=10;
                    }
                    else if(sgrid[x][y]==10){
                        sgrid[x][y]=11;
                    }
                }
            }
        }

        if(opened_cell==safe_cell){
            gameover=true;
            result=true;
        }

        SDL_RenderClear(render);
    }

    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            Game_map.Set_rect(grid[i][j]*32,0,32,32);
            Game_map.Set_pos(i*32, j*32);
            Game_map.Render();
        }
    }

    SDL_RenderPresent(render);
    SDL_Delay(1000);

    if(result == false){
        Game_map.Load_from_file("losegamemap.jpg");
    }
    else if(result == true){
        Game_map.Load_from_file("winmap.jpg");
    }

    while(!ketqua){
        Game_map.ResultMap();
        SDL_RenderPresent(render);
        while(SDL_PollEvent(&phim)!=0){
            if(phim.type == SDL_QUIT)
            {
                return 0;
            }
            if(phim.type==SDL_KEYDOWN){
                if(phim.key.keysym.sym==SDLK_SPACE){
                    return Game_play();
                }
            }
        }
    }

}
