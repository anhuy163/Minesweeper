#ifndef DATASOLVING_H_INCLUDED
#define DATASOLVING_H_INCLUDED
#include<cstdlib>
#include<SDL.h>

int dem_bom(int x, int y);
int dem_co(int x, int y);
void Game_preparation();
void Open_cell(int x, int y);
int Game_play();

#endif // DATASOLVING_H_INCLUDED
