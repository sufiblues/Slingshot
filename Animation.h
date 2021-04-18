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
// len(frame_time) == len(frames) each index corresponds to which sprite plays on which frame from the start time.
	std::vector<int> frame_time;
	int start_time;
	int current_frame;
} Animation;

/** Render animation at that specific frame */
void renderAnimation(Animation* a, glm::vec2 pos);

/** add a frame to the animation */
void addFrame(Animation* a, TextureID tid);

/** add a frame to the animation given filename */
void addFrame(Animation* a, int time, std::string filepath);

/** pop frame off of the animation list */
void removeFrame(Animation* a);
