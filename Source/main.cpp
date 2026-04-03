
#include "calculations.h"

void new_frame(SDL_Window* window, SDL_Surface* screen, params_t params);

#define NEW_FRAME new_frame(window, screen, params);

int main() {
    SDL_Window* window = NULL;
    SDL_Surface* screen = NULL;
    
    if (create_window(&window, &screen) != 0) {
        return 1;
    }

    SDL_Event event;
    int running = 1;

    params_t params = {
        .dx = -250,
        .dy = -150,
        .increasing = 0.01f,
        .speed = 2,
    };

    NEW_FRAME    

    while (running) {
        
        const Uint8* keystate = SDL_GetKeyboardState(NULL);

        if (keystate[SDL_SCANCODE_UP])    {params.dy -= params.speed; NEW_FRAME}
        if (keystate[SDL_SCANCODE_DOWN])  {params.dy += params.speed; NEW_FRAME}
        if (keystate[SDL_SCANCODE_RIGHT]) {params.dx += params.speed; NEW_FRAME}
        if (keystate[SDL_SCANCODE_LEFT])  {params.dx -= params.speed; NEW_FRAME}

        if (keystate[SDL_SCANCODE_Z])  params.speed += 0.5f;
        if (keystate[SDL_SCANCODE_X])  params.speed -= 0.5f;

        if (keystate[SDL_SCANCODE_KP_MINUS]) {params.increasing *= 1.01f; NEW_FRAME}
        if (keystate[SDL_SCANCODE_KP_PLUS])  {params.increasing *= 0.99f; NEW_FRAME}

        if (keystate[SDL_SCANCODE_R])  {params = {-250, -150, 0.01f, 2}; NEW_FRAME}

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q) {
                printf("Q НАЖАТА (событие)! Выход...\n");
                running = 0;
            }
        }
    }
}

void new_frame(SDL_Window* window, SDL_Surface* screen, params_t params){
    calculate_set(screen, params);
    SDL_UpdateWindowSurface(window);
}