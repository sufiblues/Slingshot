#pragma once
#ifndef _CONTEXT_H
#define _CONTEXT_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


extern const int normalized_tile;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int FRAME_RATE;
extern const int FRAME_DELAY;

extern SDL_Renderer* Renderer;
extern SDL_Window* Window;

//create SDL context and intitialize packages
bool createContext();
void destroyContext();

SDL_Texture* loadTexture(std::string filename);
void closeTexture(SDL_Texture* texture);


#endif // _CONTEXT_HEADER
