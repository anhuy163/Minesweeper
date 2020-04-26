#include"texture.h"

texture Game_map;
extern SDL_Renderer* render;

void texture::Load_from_file(std::string path){
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load(path.c_str());
    texture = SDL_CreateTextureFromSurface(render, surface);
    height = surface->h;
    width = surface->w;
    maptext = texture;
    SDL_FreeSurface(surface);
}

void texture::ResultMap(){
    SDL_Rect Rpos = {0, 0, 320, 320};
    SDL_RenderCopy(render, maptext, NULL, &Rpos);
}
void texture::Render(){
    SDL_Rect Mpos = {position.x, position.y, width, height};
    SDL_RenderCopy(render, maptext, &CatAnh, &Mpos);
}

void texture::Set_pos(int x, int y){
    position.x = x;
    position.y = y;
}

void texture::Set_size(int w, int h){
    width = w;
    height = h;
}

void texture::Set_rect(int x, int y, int w, int h){
    CatAnh.x = x;
    CatAnh.y = y;
    CatAnh.w = w;
    CatAnh.h = h;
}
