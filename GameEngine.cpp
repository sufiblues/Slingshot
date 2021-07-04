
#include "GameEngine.h"

const int LEVEL_HEIGHT = normalized_tile * 18;
const int LEVEL_WIDTH = normalized_tile * 32;

//Game loop for emscirpten
void gameLoop(){

    updateInputState(&INPUTS);
    update();
    render();
}

//TODO: easier way to initialize rectangles...
void engineStart(){
   
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


    //if collision is detected then  stop
    /***
    if (tandu[0] >= 0 && tandu[0] < 1 && tandu[1] < 1 && tandu[1] >= 0){
    	printf("intersection detected %f\n", tandu[0]);
	p.velocity = tandu[0] * p.velocity;
	p.velocity = trunc(p.velocity);
	glm::vec2 pe = glm::normalize(p.velocity);
	printf("p.vel normalized (%f,%f)\n", pe[0], pe[1]);
	p.velocity = p.velocity - ceil(glm::normalize(p.velocity));
	printf("center; (%f,%f))\n", primary.center[0],primary.center[1]);
	printf("p.vel after intersection (%f,%f)\n", p.velocity[0],p.velocity[1]);
    }

    integration(&primary.center,&p);
   ***/
}

void render(){
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderClear(Renderer);
    
    SDL_RenderPresent(Renderer); 
}


