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
		return true;
	}
}

void Level::drawBlock(int i, int j, int cx, int cy){
	SDL_SetRenderDrawColor(Renderer, 52, 52, 52, 255);
	SDL_Rect temp = {i*normalized -cx , j*normalized -cy, normalized, normalized};
	SDL_RenderFillRect(Renderer, &temp);
	
}

void Level::renderBlocks(int cx, int cy){
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			if (board[i][j] == 1){
				drawBlock(i,j,cx,cy);
			}
		}
	}
}



