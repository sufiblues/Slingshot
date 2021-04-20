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
		Rectangle daEnd;
		std::vector<std::vector<int>> board;
		std::vector<std::pair<int,int>> activeblocks;
		std::vector<Rectangle> levelBlocks;
		std::vector<Rectangle> hazardBlocks;
		std::vector<TextureID> renderable;
		glm::vec2 spawn_point;
		//TOOD: change this to center point to match with naming convention of other variables
		glm::vec2 level_center;	
		glm::vec2 end_point;
		
		bool finished;

		Level(int n, int r, int c);
		~Level();
		
		void addFloor();
				
		void spawnCharacter(Player* m);
		void setSpawnPoint(int i, int j);
		void setEndPoint(int i, int j);
		void reachedEndPoint(Player* mc);

		bool addBlock(int i, int j);
		bool addHazardBlock(int i , int j);
		bool removeBlock(int i, int j);
				
		
		void printBoard();	 
		void showGridLines(int cx, int cy);
		
		void renderBlocks();
		void drawBlock(int i, int j,int cx, int cy, SDL_Color color);
		
		int playerCollideWithLevel(Circle* hitbox);	

		void playerCollideWithHazards(Player* mc);

		void loadAssets();
		void renderAssets();
		void renderBackground();
};
