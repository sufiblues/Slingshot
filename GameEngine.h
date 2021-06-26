#ifndef GAME_ENGINE
#define GAME_ENGINE


#include "Shapes.h"
#include <algorithm>
#include "Utils.h"
#include "Controller.h"
#include "Texture.h"
#include "Physics.h"
#include "glm/vec2.hpp"

#if EMSCRIPTEN
#include <emscripten.h>
#endif

extern const int LEVEL_HEIGHT;
extern const int LEVEL_WIDTH;


void loadAssets();

void initLevel();

typedef struct User User;

struct User {
    Circle hitbox;
    PhysicsComponent physics;
    bool gravity_applied;
    bool on_ground;
};



void engineStart();

void gameLoop();

void getInput();
void update();
void render();


#endif
