
#include "calculations.h"

#define NEW_FRAME new_frame(window, screen, pixel_colors, params);

// Рисуем прямоугольник из массива цветов на поверхности SDL
void draw_pixel_array(SDL_Surface* screen, uint32_t* colors, int x, int y) {
    for (int row = 0; row < rect_h; row++) {
        uint32_t* src = &colors[row * rect_w];
        uint32_t* dst = (uint32_t*)screen->pixels + (y + row) * screen->w + x;
        
        for (int col = 0; col < rect_w; col++) {
            dst[col] = src[col];
        }
    }
}


void new_frame(SDL_Window* window, SDL_Surface* screen, uint32_t* pixel_colors, params_t params){
    calculate_set(pixel_colors, screen, params);
    draw_pixel_array(screen, pixel_colors, 100, 100);
    SDL_UpdateWindowSurface(window);
}

int main() {
    SDL_Window* window = NULL;
    SDL_Surface* screen = NULL;
    
    if (create_window(&window, &screen) != 0) {
        return 1;
    }

    // Массив цветов для прямоугольника
    uint32_t* pixel_colors = (uint32_t* )calloc(rect_w * rect_h, sizeof(uint32_t));


    
    // Ждём закрытия окна
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

        if (keystate[SDL_SCANCODE_R])  params = {-250, -250, 100, 2};

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q) {
                printf("Q НАЖАТА (событие)! Выход...\n");
                running = 0;
            }
        }
    }
}

