
#include "GameEngine.h"

const int LEVEL_HEIGHT = normalized_tile * 18;
const int LEVEL_WIDTH = normalized_tile * 32;


User p;

/*~~~~Platforms for player to jump around on~~~~*/
Level one(normalized_tile, 18,32);

/*Create TIDs for future textures*/
//TODO: Figure out a better way to organize this data so it is available in the render loop
TextureID chars;
TextureID background;

void loadAssets(){
    //load textures
    
    insertTexture("chars", "assets/textures/char_test/idle0001.png");
    setTextureID(&chars, "chars");
    one.loadAssets();
    /*
    background.src.x = 0;
    background.src.y = 0;
    background.src.w = LEVEL_WIDTH;
    background.src.h = LEVEL_HEIGHT;
    insertTexture("bg", "assets/textures/smash-3.jpg", &background.src); 
    setTextureID(&background, "bg");
    */
}


void gameLoop(){
    getInput();
    update();
    render();
}

void engineStart(){

    loadAssets();
    one.addBlock(17, 30);

    p.on_ground = false;
    p.gravity_applied = false;
    p.hitbox.radius = normalized_tile;
    p.hitbox.center = glm::vec2(normalized_tile * 0, normalized_tile * 0);

    p.hitbox.center[0] = LEVEL_WIDTH / 2;
    p.hitbox.center[1] = LEVEL_HEIGHT / 2;



	int frame_start;
    int elapsed_ticks;

#ifdef EMSCRIPTEN
    emscripten_set_main_loop(gameLoop, 0, 1);
#else
	while(!INPUTS.quit){
		
		frame_start = SDL_GetTicks();

		gameLoop();

		elapsed_ticks = SDL_GetTicks() - frame_start;

        if (elapsed_ticks  < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - elapsed_ticks);
        }
	}
#endif



}

void getInput(){
	updateInputState(&INPUTS);
}

void update(){

    camera.x = p.hitbox.center[0] - SCREEN_WIDTH / 2;
    camera.y = p.hitbox.center[1] - SCREEN_HEIGHT / 2;

    //Keep the camera in bounds
    
    if (camera.x < 0)
    {
        camera.x = 0;
    }
    if (camera.y < 0)
    {
        camera.y = 0;
    }
    if (camera.x > LEVEL_WIDTH - camera.w)
    { 
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if (camera.y > LEVEL_HEIGHT - camera.h)
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }

    
    int flag = one.playerCollideWithLevel(&p.hitbox);
     
    if (INPUTS.left && flag != 1) {
        addMomentum(&p.physics, glm::vec2(-4, 0));
    }
    if (INPUTS.right && flag != 2) {
        addMomentum(&p.physics, glm::vec2(4, 0));
    }
    if (flag == 1){
        removeHorizontalMomentum(&p.physics);
    }
    if (flag == 2){
        removeHorizontalMomentum(&p.physics);
    }
    if (!p.on_ground && !p.gravity_applied) {

        //add gravity
        addForce(&p.physics, glm::vec2(0, 1));
        p.gravity_applied = true;
    }
    //todo::remove when collision with rectangles gets fleshed out
    //if player hits the ground 
    //need to dispace distance when hit ground
    if (p.hitbox.center[1] + p.hitbox.radius > LEVEL_HEIGHT) {

        p.on_ground = true;
        p.hitbox.center[1] = LEVEL_HEIGHT - p.hitbox.radius;
        //remove gravity
        removeVerticalForce(&p.physics);
        removeVerticalMomentum(&p.physics);
        p.gravity_applied = false;
    }

    if (INPUTS.jump && p.on_ground) {

        addMomentum(&p.physics, glm::vec2(0,-30));
        p.on_ground = false;

    }

    addFriction(&p.physics);
    integration(&p.hitbox.center, &p.physics);
    
}

void render(){

    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderClear(Renderer);

    //RenderTextureID(&background,0,0, &camera);

    glm::vec2 something = glm::vec2(p.hitbox.center[0] - camera.x, p.hitbox.center[1] - camera.y);

    //RenderTextureID(&chars,something ); 
    RenderTextureID(&chars, 0, 0, &camera);
    RenderShape(&p.hitbox,red,camera.x,camera.y);
    
     
    one.showGridLines(camera.x, camera.y);
    one.renderBlocks(camera.x, camera.y);
    one.renderAssets(camera.x, camera.y);
    
    SDL_RenderPresent(Renderer);

}


