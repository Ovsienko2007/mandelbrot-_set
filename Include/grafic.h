#ifndef GRAFIC_H_
#define GRAFIC_H_

#include <SDL2/SDL.h>

static const int cWindowWidth  = 800;
static const int cWindowHeight = 600;

static const size_t rect_w = 500;
static const size_t rect_h = 500;

int create_window(SDL_Window** window, SDL_Surface** screen);

#endif