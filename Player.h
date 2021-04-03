#pragma once
#include <vector>
#include "Shapes.h"
#include "Physics.h"
#include "Utils.h"
#include "Context.h"
#include "Texture.h"

typedef struct Player {
	Rectangle hitbox;
	PhysicsComponent physics;
	int state;
	TextureID image;

}Player;

enum DirectionFlags {
	TOP = 1 << 0,
	BOTTOM = 1 << 1,
	LEFT = 1 << 2,
	RIGHT = 1 << 3
};

enum PlayerState {
	GROUNDED = 1 << 0,
	LEAN_WALL_LEFT = 1 << 1,
	LEAN_WALL_RIGHT = 1 << 2,
	RUN = 1 << 3,
	DASH = 1 << 4,
	JUMP = 1 << 5,
	LANDING = 1 << 6,
	AERIAL = 1 << 7
};

/** Gets all directions of collision from the level */
int collisionEnumeration(Player* mc, std::vector<Rectangle> lvlBlocks);

/** takes collision directions and updates player state */
int stateResolution(Player* mc,  int collisions);

/** takes player state and inputs to update physics component */
void updatePhysics(Player* mc);


