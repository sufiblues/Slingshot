
#include "GameEngine.h"

const int LEVEL_HEIGHT = normalized_tile * 18;
const int LEVEL_WIDTH = normalized_tile * 32;



Rectangle primary;
Rectangle secondary; 

/*Create TIDs for future textures*/
//TODO: Figure out a better way to organize this data so it is available in the render loop
TextureID chars;
TextureID background;
TextureID monster;
TextureID text;

SDL_Texture* test;

//load assets for all entities
void loadAssets(){
    //load textures
    insertMusic("banger", "assets/06 STARMINE.mp3");
    insertSoundEffect("jump", "assets/soundeffect.wav");
    insertFont("font","assets/font.ttf", 24);
    createTextureFromFont("testTitle", "font_24", "Hello World");
    test = queryTexture("testTitle");
    setTextureID(&text, "testTitle");

}

//Game loop for emscirpten
void gameLoop(){

    updateInputState(&INPUTS);
    update();
    render();
}

//TODO: easier way to initialize rectangles...
void engineStart(){
    primary.center = glm::vec2(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    primary.width = 50;
    primary.height = 50;
	
    secondary.center = glm::vec2(normalized_tile * 10, normalized_tile*2);
    secondary.width = 50;
    secondary.height = 50;

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


void update(){

    //Keep the camera in bounds    
    //TODO: add function for camera update
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
    //add inputs
    if (INPUTS.left == 1){
    	primary.center[0] -= 5;
    } 
    if (INPUTS.right == 1){
    	primary.center[0] += 5;
    }
    if (INPUTS.up == 1){
    	primary.center[1] -= 5;
    }
    if (INPUTS.down == 1){
    	primary.center[1] += 5;
    }

	
    collisionRectangleAndRectangle(primary, secondary);
    

}

void render(){
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderClear(Renderer);
    
    RenderShape(&primary,red);
    RenderShape(&secondary, green);     

    SDL_RenderPresent(Renderer); 
}


