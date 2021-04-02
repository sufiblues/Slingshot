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

	
	/*
	for (int i = 0; i < rows; i++){
		board.push_back(std::vector<int>);
		board[i].reserve(columns);
		for (int j = 0; j < columns; j++){
			board[i][j] = 0;
		}
	}
	*/
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


