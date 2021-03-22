#pragma once

#include "Context.h"

typedef struct Controller {
	int up = 0;
	int down = 0;
	int left = 0;
	int right = 0;
	int jump = 0;
	int attack = 0;
	int shield = 0;
	bool quit = 0;
    int click = 0;
    int touch = 0;
    SDL_Point mPosition = {0,0};

} Controller;

extern SDL_Event event;

extern Controller INPUTS;

void updateInputState(Controller* controller);