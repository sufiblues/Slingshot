#include "Level.h"

Level::~Level(){

}

Level::Level(int n, int r,int c){
	rows = r;
	columns = c;
	normalized = n;

	for (int i =0;i<rows;i++){
		std::vector<int> temp;
		temp.reserve(columns);
		for (int j = 0;j<columns;j++){
			temp.push_back(0);
		}
		board.push_back(temp);
	}	
}

void Level::printBoard(){
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			printf(" %d ", board[i][j] );
		}
		printf("\n");
	}
}

void Level::showGridLines(int cx, int cy){
	SDL_SetRenderDrawColor(Renderer, 0xff,0xff,0xff,0xff);
	for (int i = 0; i<rows; i++){
		SDL_RenderDrawLine(Renderer, 0-cx, i * normalized -cy, columns*normalized -cx, i*normalized -cy);
	}
	for (int j=0; j<columns;j++){
		SDL_RenderDrawLine(Renderer , j*normalized -cx, 0 -cy, j*normalized -cx, rows*normalized -cy);
	}
}

bool Level::addBlock(int i, int j){
	if ((i >= rows) || (j >= columns) || i < 0 || j < 0){
		return false;
	}
	if (board[i][j] != 0){
		return false;
	}
	else{
		board[i][j] = 1;
		activeblocks.push_back(std::make_pair(i,j));
		Rectangle temp = {glm::vec2(j*normalized + normalized/2 , i*normalized + normalized/2 ), normalized, normalized};
		levelBlocks.push_back(temp);
		return true;
	}
}

void Level::loadAssets(){
	TextureID background = {SDL_Rect{0,0,normalized*columns,normalized*rows}, "bg"};	
	insertTexture("bg", "asset/textures/smash-3.jpg", &background.src);
	setTextureID(&background, "bg");
}

void Level::renderAssets(int cx , int cy){
	for (int i = 0; i < renderable.size(); i++){
		RenderTextureID(&renderable[i], camera.x, camera.y);
	}
}

void Level::drawBlock(int rp, int cp, int cx, int cy){
	SDL_SetRenderDrawColor(Renderer, 0, 255, 100, 255);
	SDL_Rect temp = {cp*normalized -camera.x , rp*normalized -camera.y, normalized, normalized};
	SDL_RenderFillRect(Renderer, &temp);	
}

void Level::renderBlocks(int cx, int cy){
	for (int i = 0; i < activeblocks.size(); i++){
		drawBlock(activeblocks[i].first,activeblocks[i].second,cx,cy);
	}
}

int Level::playerCollideWithLevel(Circle* hitbox){
	int temp = 0;
	for (int i = 0; i < levelBlocks.size(); i++){
		temp = directionOfHit(hitbox, &levelBlocks[i]);
		if (temp != 0 ){
			return temp;
		} 
	}
	return temp;
}
