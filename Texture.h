#pragma once
#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>
#include "AssetManager.h"
#include "Shapes.h"
#include "Utils.h"

//renamme to id
typedef struct TextureID {
	SDL_Rect src;
	std::string name;
}TextureID;

void RenderTextureID(TextureID* tid, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, bool FIXED_LOCATION = false);
//this helps match up the hitbox and the sprite clip
void RenderTextureID(TextureID* tid, glm::vec2 pos, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, bool FIXED_LOCATION = false);
//Set texture name so it is easier to call
//ex. characterTexture(TID)->return graphicsManager[TID.name]
void setTextureID(TextureID* tid, std::string name);


#endif
