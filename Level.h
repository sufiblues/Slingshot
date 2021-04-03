#pragma once 

#include <utility>
#include <vector>
#include "Texture.h"
#include "Context.h"
#include "Shapes.h"
#include "Utils.h"
#include "Player.h"

class Level {
	public:
		int normalized;
		int rows;
		int columns;
		std::vector<std::vector<int>> board;
		std::vector<std::pair<int,int>> activeblocks;
		std::vector<Rectangle> levelBlocks;
		std::vector<TextureID> renderable;
		glm::vec2 level_center;	
		

		Level(int n, int r, int c);
		~Level();
		
		void addFloor();

		bool addBlock(int i, int j);
		bool removeBlock(int i, int j);
		
		void printBoard();	 
		void showGridLines(int cx, int cy);
		
		void renderBlocks();
		void drawBlock(int i, int j,int cx, int cy);
		
		int playerCollideWithLevel(Circle* hitbox);	

		void loadAssets();
		void renderAssets();
		void renderBackground();
};
