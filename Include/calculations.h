#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

#include "grafic.h"

struct params_t{
    float dx;
    float dy;
    float increasing;
    float speed;
};

int calculate_set(uint32_t *pixel_colors, SDL_Surface *screen, params_t params);
#endif