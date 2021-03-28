

#include <math.h>

#include "Context.h"
#include "Shapes.h"
#include "Physics.h"
#include "AssetManager.h"
#include "Texture.h"
#include "Controller.h"
#include "GameEngine.h"



//const int LEVEL_WIDTH = 1280;
//const int LEVEL_HEIGHT = 960;





struct MovableObject {
    Circle hitbox = { glm::vec2(0.0f, 0.0f) , normalized_tile/2 };
    PhysicsComponent physics;
    bool on_ground;
};

//MovableObject player;
MovableObject bullet;


/*
//TODO: fiund more elegant solution for angles and negative values
void shootBulletTowards(SDL_Point* click_position) {

    glm::vec2 pt_start = player.pos;
    glm::vec2 pt_end = glm::vec2(click_position->x, click_position->y);

    glm::vec2 direction = pt_end - pt_start;
    direction = glm::normalize(direction);

    bullet.pos = player.pos;
    bullet.hitbox.center = player.pos;

    bullet.velocity = direction * BULLET_SPEED; 
}
*/

SDL_Rect platform = { normalized_tile*0, normalized_tile*4, normalized_tile*7, normalized_tile*4 };
Rectangle platf = { glm::vec2(platform.x + platform.w / 2, platform.y + platform.h / 2), platform.w, platform.h};


/*
void recoil(MovableObject* obj, int dirofhit) {

    //if hit from left or right
    if (dirofhit == 1 || dirofhit == 2) {
        obj->velocity[0] = -obj->velocity[0];
    }
    if (dirofhit == 3 || dirofhit == 4) {
        obj->velocity[1] = -obj->velocity[1];
    }
    if (dirofhit == 5) {
        obj->velocity = -1.0f * obj->velocity;
    } 
}
*/

void printRect(SDL_Rect rect) {
    printf("[%d %d %d %d]\n", rect.x, rect.y, rect.w, rect.h);
}
bool gravity_applied = false;
int main(int argc, char* args[]) {

	createContext();



    /*

    //player.hitbox.center = glm::vec2(normalized_tile * 0, normalized_tile * 0);

    SDL_Rect camera = { 0,0, SCREEN_WIDTH,SCREEN_HEIGHT };

    std::string dustkid_filename = "textures.f";
    std::string bg_filename = "textures/logolight.png";
    insertTexture("dustkid", dustkid_filename);
    insertTexture("bg", bg_filename);
    TextureID dustkid;
    setTextureID(&dustkid, "dustkid");
    TextureID background;
    setTextureID(&background, "bg");

    printRect(dustkid.src);
    printRect(background.src);

    player.hitbox.center[0] = LEVEL_WIDTH / 2;
    player.hitbox.center[1] = LEVEL_HEIGHT / 2;
    

    while (!INPUTS.quit) {


        updateInputState(&INPUTS);
    

        
        //TODO convert dimensions into 2d glm vectors
        camera.x = player.hitbox.center[0] - SCREEN_WIDTH / 2;
        camera.y = player.hitbox.center[1] - SCREEN_HEIGHT / 2;

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
        
        SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
        SDL_RenderClear(Renderer);

        RenderTextureID(&background,0,0, &camera);

        glm::vec2 something = glm::vec2(player.hitbox.center[0] - camera.x, player.hitbox.center[1] - camera.y);

        RenderTextureID(&dustkid,something );
        
        RenderShape(&player.hitbox, red,camera.x, camera.y);

        
        
        SDL_RenderPresent(Renderer);
       

        
    }


    //TODO write a function that closes the asset manager
    removeTexture("dustkid");
    removeTexture("bg");
*/
    engineStart();
    
    destroyContext();
 
	return 0;
}
