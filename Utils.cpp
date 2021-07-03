#include "Utils.h"

SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

SDL_Color red = { 255, 0, 0, 255 };
SDL_Color green = { 0, 255, 0, 255 };
SDL_Color blue = { 0, 0, 255, 255 };
SDL_Color cyan = {0,255,255,255};

float roundFloat(float num, int decimal_places){
    float divisor = pow(10.0f,decimal_places);
    return  roundf(num * divisor)/divisor;

}
