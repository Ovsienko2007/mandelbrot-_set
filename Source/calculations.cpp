#include "calculations.h"
#include <stdio.h>

static void add_arrsf   (float *x  , float *y);
static void sub_arrsf   (float *x  , float *y);
static void mull_arrsf  (float *ans, float *x, float *y);
static void assign_arrsf(float *x  , float *y);

static void compare_arrs(uint8_t *is_need, float *x, float *y);

static void add_arrui8     (uint8_t *x, uint8_t *y);
static void mull_arrui8    (uint8_t *x, uint8_t *y);
static void assign_arrui8  (uint8_t *x, uint8_t *y);
static void assign_arrui32 (Uint32 *x, Uint32 *y);

static bool eq_arrs (uint8_t *x, uint8_t *y);
static bool eq_arrs2(uint8_t *x, uint8_t *y);

static void get_colors (Uint32 *ans, uint8_t *r, uint8_t *g, uint8_t *b, SDL_Surface *screen);

int calculate_set(SDL_Surface *screen, params_t params){
    float xf[4]  , yf[4];
    float xf_2[4], yf_2[4];
    uint8_t arr_r[4], arr_g[4], arr_b[4];
    Uint32 col_arr[4];

    uint32_t* pixels = (uint32_t*)screen->pixels;

    float x_d1[4]  = {0,1,2,3};
    uint8_t arr_0[4]  = {0,0,0,0};
    uint8_t arr_10[4] = {10,10,10,10};


    float increasing[4] = {params.increasing, params.increasing, params.increasing, params.increasing};
    float d_x[4]        = {params.dx        , params.dx        , params.dx        , params.dx        };
    float d_y[4]        = {params.dy        , params.dy        , params.dy        , params.dy        };
    
    for (size_t y = 0; y < rect_h; y++) {
        for (size_t x = 0; x < rect_w; x += 4) {
            float x0[4] = {(float)x, (float)x, (float)x, (float)x};
            float y0[4] = {(float)y, (float)y, (float)y, (float)y};

            add_arrsf(x0, x_d1);

            add_arrsf(x0, d_x);
            add_arrsf(y0, d_y);

            mull_arrsf(x0, x0, increasing);
            mull_arrsf(y0, y0, increasing);

            assign_arrsf(xf, x0);
            assign_arrsf(yf, y0);

            mull_arrsf(xf_2, xf, xf);
            mull_arrsf(yf_2, yf, yf);

            uint8_t is_need[4] = {1,1,1,1};
            uint8_t n[4] = {1,1,1,1};


            while (eq_arrs2(n, arr_0) && !eq_arrs(is_need, arr_0)){
                mull_arrsf(yf, yf, xf);
                add_arrsf(yf, yf);
                add_arrsf(yf, y0);

                assign_arrsf(xf, xf_2);
                sub_arrsf(xf, yf_2);
                add_arrsf(xf, x0);

                mull_arrsf(xf_2, xf, xf);
                mull_arrsf(yf_2, yf, yf);

                compare_arrs(is_need, xf_2, yf_2);
                add_arrui8(n, is_need);
            }

            mull_arrui8(n, arr_10);

            assign_arrui8(arr_r, n);
            assign_arrui8(arr_g, n);
            assign_arrui8(arr_b, n);

            get_colors(col_arr, arr_r, arr_g, arr_b, screen);

            assign_arrui32(&(pixels[(y + 100) * screen->w + (x + 100)]), col_arr);
        }
    }

    return 0;
}

void add_arrsf   (float *x, float *y) {for (int i = 0; i < 4; i++){ x[i] += y[i]; }}
void sub_arrsf   (float *x, float *y) {for (int i = 0; i < 4; i++){ x[i] -= y[i]; }}
void mull_arrsf  (float *ans, float *x, float *y) {for (int i = 0; i < 4; i++){ ans[i] = x[i] * y[i]; }}
void assign_arrsf(float *x, float *y) {for (int i = 0; i < 4; i++){ x[i]  = y[i]; }}

void compare_arrs(uint8_t *is_need, float *x, float *y) {for (int i = 0; i < 4; i++){ is_need[i] = ((x[i] + y[i]) < 4); }}

void add_arrui8     (uint8_t *x, uint8_t *y) {for (int i = 0; i < 4; i++){ x[i] += y[i]; }}
void mull_arrui8    (uint8_t *x, uint8_t *y) {for (int i = 0; i < 4; i++){ x[i] *= y[i]; }}
void assign_arrui8  (uint8_t *x, uint8_t *y) {for (int i = 0; i < 4; i++){ x[i] = y[i]; }}

void assign_arrui32 (Uint32 *x, Uint32 *y) {for (int i = 0; i < 4; i++){ x[i] = y[i]; }}

void get_colors (Uint32 *ans, uint8_t *r, uint8_t *g, uint8_t *b, SDL_Surface *screen) {
    for (int i = 0; i < 4; i++){ 
        ans[i] = SDL_MapRGB(screen->format, r[i], g[i], b[i]);
    }
}

bool eq_arrs(uint8_t *x, uint8_t *y) {
    for (int i = 0; i < 4; i++){ 
        if (x[i] != y[i]) return false;
    }
    return true;
}
bool eq_arrs2(uint8_t *x, uint8_t *y) {
    for (int i = 0; i < 4; i++){ 
        if (x[i] == y[i]) return false;
    }
    return true;
}