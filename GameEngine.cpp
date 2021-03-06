
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
TextureID text;

SDL_Texture* test;

//load assets for all entities
void loadAssets(){
    //load textures
    one.loadAssets();    
    loadAssets(&mc);
    insertMusic("banger", "assets/06 STARMINE.mp3");
    insertSoundEffect("jump", "assets/soundeffect.wav");
    insertFont("font","assets/font.ttf", 24);
    createTextureFromFont("testTitle", "font_24", "Hello World");
    test = queryTexture("testTitle");
    setTextureID(&text, "testTitle");

}

//Game loop for emscirpten
void gameLoop(){
    getInput();
    update();
    render();
}

void initLevelOne(){
    one.addFloor();
    one.addBlock(one.rows - 2, 3);
    one.addBlock(one.rows - 2, 5);
    one.addBlock(one.rows - 3,6);
    one.addBlock(one.rows -3,7);
    one.addHazardBlock(one.rows - 2,8);
    one.addBlock(one.rows - 3,9);
    one.addHazardBlock(one.rows-2,10);
    one.addBlock(one.rows - 3,11);
    one.addBlock(one.rows - 3,12);
    one.addHazardBlock(one.rows - 2,13);
    one.addBlock(one.rows - 3,14);
    one.addBlock(one.rows - 4,15); 
    one.setEndPoint(5,16);

    one.setSpawnPoint(1,1); 
    one.spawnCharacter(&mc);
}

void engineStart(){
    loadAssets();
    
    initLevelOne();
    one.Serialize();
    one.Deserialize("pretty.json");
    // Mix_PlayMusic(MusicManager["banger"], -1);
    mc.hitbox.width = normalized_tile/2;
    mc.hitbox.height = normalized_tile*1;
    
	  int frame_start;
    int elapsed_ticks;

#ifdef EMSCRIPTEN
    emscripten_set_main_loop(gameLoop, 0, 1);
#else
	  while(!INPUTS.quit){
		
		    frame_start = SDL_GetTicks();
		    gameLoop();
        if (one.finished){
            printf("You Won!\n");
            break;
        }
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
    one.playerCollideWithHazards(&mc);
    one.reachedEndPoint(&mc);
}

void render(){
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderClear(Renderer);
    
    one.renderBackground();
         
    one.showGridLines(camera.x, camera.y);
    one.renderBlocks();
    RenderShape(&mc.hitbox, blue, camera.x, camera.y);
    RenderShape(&one.daEnd, blue, camera.x, camera.y);
    render(&mc);

    RenderTextureID( &text, glm::vec2(9,9) , NULL, 0.0,  NULL, SDL_FLIP_NONE, true);
    SDL_RenderPresent(Renderer); 
}


