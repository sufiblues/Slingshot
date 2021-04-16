#pragma once

#include "Context.h"
#include "Utils.h"
#include "AssetManager.h"
#include "Texture.h"
#include "Shapes.h"
#include "glm/vec2.hpp"
#include <vector>

typedef struct Animation{
	std::vector<TextureID> frames;
	std::string name;
} Animation;

/** Render animation at that specific frame */
void renderAnimation(Animation* a, glm::vec2 pos,  int frame);

/** add a frame to the animation */
void addFrame(Animation* a, TextureID tid);

/** add a frame to the animation given filename */
void addFrame(Animation* a, std::string filepath);

/** pop frame off of the animation list */
void removeFrame(Animation* a);
