#include "Player.h"

//TODO: Change the input vector to reference instead of a pointer
int collisionEnumeration(Player* mc ,std::vector<Rectangle>  lvlBlocks){
	int res = 0;
	for (int i = 0; i < lvlBlocks.size(); i++){
		
		res = collisionRectangleAndRectangle(mc->hitbox,  lvlBlocks[i]) | res;
	}
	return res;
}

int stateResolution(Player* mc , int collisions){
	if (collisions & BOTTOM){		 
		mc->physics.velocity[1] = fmin(0, mc->physics.velocity[1]);
    mc->physics.acceleration[1] = fmin(0, mc->physics.acceleration[1]);
		mc->state = GROUNDED;
	}
	else if (collisions & TOP){  
		mc->physics.velocity[1] = fmax(0, mc->physics.velocity[1]);
    mc->physics.acceleration[1] = fmax(0, mc->physics.acceleration[1]);
		mc->state = mc->state & ~GROUNDED;
	}
	else{	
		mc->state = mc->state & ~GROUNDED;
	}
	if (collisions & LEFT) {
    mc->physics.velocity[0] = fmax(0, mc->physics.velocity[0]);
    mc->physics.acceleration[0] = fmax(0, mc->physics.acceleration[0]);
		mc->state = mc->state | LEAN_WALL_LEFT;
	}
	else if (collisions & RIGHT){
    mc->physics.velocity[0] = fmin(0, mc->physics.velocity[0]);
    mc->physics.acceleration[0] = fmin(0, mc->physics.acceleration[0]);
		mc->state = mc->state | LEAN_WALL_RIGHT;
	}
	
	return mc->state;
}


void addInputs(Player* mc){
	mc->frame += 1;
	if (mc->frame > 12){
		mc->frame = 0;
	}
	//if player is not grounded then add gravity
	if((mc->state & GROUNDED) == 0){
		addForce(&mc->physics, glm::vec2(0,1));
	}
	else{
		//if grounded and user inputs jump
		if ((mc->state & GROUNDED) && INPUTS.jump){
			addMomentum(&mc->physics,glm::vec2(0,-30));
		}
	}	
  if (INPUTS.left ) {
      addMomentum(&mc->physics, glm::vec2(-4, 0));
	}
  if (INPUTS.right ) {
      addMomentum(&mc->physics, glm::vec2(4, 0));
  }
}

void setPlayerLocation(Player* mc, int x_cord, int y_cord){
	mc->hitbox.center = glm::vec2(x_cord, y_cord);	
}

void loadAssets(Player *mc ){
	mc->images.name = "idle";
	mc->frame = 0;
	addFrame(&mc->images,0, "assets/textures/char_test/idle0001.png");	
	addFrame(&mc->images,3,"assets/textures/char_test/idle0002.png");
	addFrame(&mc->images,6,"assets/textures/char_test/idle0003.png");
	addFrame(&mc->images,9, "assets/textures/char_test/idle0004.png");
	addFrame(&mc->images,12, "assets/textures/char_test/idle0005.png");
	addFrame(&mc->images,15,"assets/textures/char_test/idle0006.png");
	

	//insertTexture("char", "assets/textures/char_test/idle0001.png");
	//setTextureID(&mc->image, "char");
}

void render(Player *mc){
	renderAnimation(&mc->images,mc->hitbox.center);	
	//RenderTextureID(&mc->image, mc->hitbox.center);
}

void updatePlayer(Player* mc, std::vector<Rectangle> lvl){
	
  camera.x = mc->hitbox.center[0] - SCREEN_WIDTH / 2;
  camera.y = mc->hitbox.center[1] - SCREEN_HEIGHT / 2;

	int colider = collisionEnumeration(mc, lvl);
	stateResolution(mc, colider);  
	addInputs(mc);
	addFriction(&mc->physics);
	integration(&mc->hitbox.center, &mc->physics); 
	
}

