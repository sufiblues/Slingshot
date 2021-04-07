
#include "GameEngine.h"

const int LEVEL_HEIGHT = normalized_tile * 18;
const int LEVEL_WIDTH = normalized_tile * 32;


//User p;
User m;

Player mc;

/*~~~~Platforms for player to jump around on~~~~*/
Level one(normalized_tile, 18,32);

/*Create TIDs for future textures*/
//TODO: Figure out a better way to organize this data so it is available in the render loop
TextureID chars;
TextureID background;
TextureID monster;

void loadAssets(){
    //load textures
    
    insertTexture("monster", "assets/textures/logolight.png");
    setTextureID(&monster, "monster");

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
    one.addFloor();
    one.addBlock(one.rows - 2, 15);


    mc.hitbox.center = glm::vec2(LEVEL_WIDTH/4, LEVEL_HEIGHT/4 );
    mc.hitbox.width = normalized_tile;
    mc.hitbox.height = normalized_tile;
    
    /*
    p.on_ground = false;
    p.gravity_applied = false;
    p.hitbox.radius = normalized_tile;
    p.hitbox.center = glm::vec2(normalized_tile * 0, normalized_tile * 0);
    
    p.hitbox.center[0] = LEVEL_WIDTH / 2;
    p.hitbox.center[1] = LEVEL_HEIGHT / 2;
    
    m.hitbox.center[0] = normalized_tile * 1;
    m.hitbox.center[1] = normalized_tile * 10;
    */
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


    updatePlayer(&mc, one.levelBlocks);
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

}

void render(){

    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderClear(Renderer);
    
    one.renderBackground();
    
    //RenderTextureID(&background,0,0, &camera);

    //RenderTextureID(&chars,p.hitbox.center ); 
    //RenderShape(&p.hitbox, red, camera.x, camera.y);
    //RenderShape(&mc.hitbox, blue, camera.x, camera.y );
     
    one.showGridLines(camera.x, camera.y);
    one.renderBlocks();
    RenderShape(&mc.hitbox, blue, camera.x, camera.y);
    SDL_RenderPresent(Renderer);

}


