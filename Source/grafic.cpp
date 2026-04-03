#include "grafic.h"

int create_window(SDL_Window** window, SDL_Surface** screen){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL не инициализирована: %s\n", SDL_GetError());
        return 1;
    }

    *window = SDL_CreateWindow("Разноцветный прямоугольник",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          cWindowWidth, cWindowHeight,
                                          SDL_WINDOW_SHOWN);

    if (*window == NULL) {
        printf("Не удалось создать окно");
        return -1;
    }

    *screen = SDL_GetWindowSurface(*window);

    if (*screen == NULL) {
        printf("Не удалось получить поверхность");
        return -1;
    }

    SDL_FillRect(*screen, NULL, SDL_MapRGB((*screen)->format, 0, 0, 0));

    return 0;
}