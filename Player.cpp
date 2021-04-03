#include "Player.h"

//TODO: Change the input vector to reference instead of a pointer
int collisionEnumeration(Player* mc ,std::vector<Rectangle>  lvlBlocks){
	int res = 0;
	int temp = 0;
	for (int i = 0; i < lvlBlocks.size(); i++){
		
		res = collisionRectangleAndRectangle(&mc->hitbox,  lvlBlocks[i]) | res;
	}
	return res;
}

int stateResolution(Player* mc , int collisions){
	if (collisions == BOTTOM){
		mc->state = GROUNDED;
	}
	else{
		mc->state = 0;
	}

	if (collisions == LEFT) { 
		mc->state = mc->state | LEAN_WALL_LEFT;
	}
	else if (collisions == RIGHT){
		mc->state = mc->state | LEAN_WALL_RIGHT;
	}

	return mc->state;

}

void updatePhysics(Player *mc){
	switch(mc->state){
		case GROUNDED:
			removeVerticalForce(&(mc->physics));
			removeVerticalMomentum(&(mc->physics));
		case ~GROUNDED:
			addMomentum(&(mc->physics), glm::vec2(0,1));			
	}
}


