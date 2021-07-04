#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include "Texture.h"
#include "Context.h"
#include "Shapes.h"
#include "Utils.h"
#include "Player.h"
#include "nlohmann/json.hpp"

typedef struct Level{
    int WIDTH; //Whole number
    int HEIGHT;
    int NORMAL; //the pixel height of the level is NORMAL * HEIGHT ex 48 * 10 units
    std::vector<Line> Boundries;
    
} Level;


void showGridLines(Level level, int camera_x, int camera_y){
	SDL_SetRenderDrawColor(Renderer, 0xff,0xff,0xff,0xff);

	for (int i = 0; i<level.HEIGHT; i++){
		SDL_RenderDrawLine(Renderer, 0 - camera_x, i * level.NORMAL - camera_y , level.WIDTH*level.NORMAL -camera_x, i*level.NORMAL-camera_y);
	}

	for (int j=0; j<level.WIDTH;j++){
		SDL_RenderDrawLine(Renderer , j*level.NORMAL -camera_x, 0 -camera_y, j*level.NORMAL -camera_x, level.HEIGHT*level.NORMAL -camera_y);
	}
}
