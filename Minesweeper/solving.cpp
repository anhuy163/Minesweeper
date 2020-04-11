#include "solving.h"

extern SDL_Window* cua_so ;

extern SDL_Renderer* render ;

extern SDL_Texture *map1, *gameoverimg, *win;

void close()
{
    SDL_DestroyWindow(cua_so);
    cua_so = NULL;
    SDL_DestroyRenderer(render);
    render = NULL;
    SDL_DestroyTexture(map1);
    map1 = NULL;
    SDL_DestroyTexture(gameoverimg);
    gameoverimg = NULL;
    SDL_Quit();
}


SDL_Texture* LoadTexture(std::string path){
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load(path.c_str());
    //SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF ));
    texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    return texture;
}


