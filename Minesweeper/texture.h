#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#include<SDL.h>
#include<iostream>
#include<SDL_image.h>
class texture{
    int height;
    int width;
    SDL_Point position;
    SDL_Texture* maptext;
    SDL_Rect CatAnh;
public:
    void Load_from_file(std::string path);

    void Render();

    void Set_size(int w, int h);

    void Set_pos(int x, int y);

    void Set_rect(int x, int y, int w, int h);

};


#endif // TEXTURE_H_INCLUDED
