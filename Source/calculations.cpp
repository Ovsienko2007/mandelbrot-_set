#include "calculations.h"

int calculate_set(uint32_t *pixel_colors, SDL_Surface *screen, params_t params){    
    for (size_t y = 0; y < rect_h; y++) {
        for (size_t x = 0; x < rect_w; x++) {
            // Начальные координаты (c = x + iy)
            float fx = (((float)x + params.dx) * params.increasing);
            float fy = (((float)y + params.dy) * params.increasing);

            float fx0 = fx;
            float fy0 = fy;


            float fx_2 = fx * fx;
            float fy_2 = fy * fy;
            
            unsigned char n = 1;
            for (; n != 0 && fx_2 + fy_2 < 4.0f; n++) {
                fy = 2.0f * fx * fy + fy0;
                fx = fx_2 - fy_2 + fx0;

                fx_2 = fx * fx;
                fy_2 = fy * fy;
            }
            
            // Цвет от количества итераций
            uint8_t brightness = (n * 10) %256;
            uint8_t r = brightness;
            uint8_t g = brightness * 0.6;
            uint8_t b = brightness * 0.2;
            
            pixel_colors[y * rect_w + x] = SDL_MapRGB(screen->format, r, g, b);
        }
    }
    
    return 0;
}