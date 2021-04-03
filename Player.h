#pragma once
#include <vector>
#include "Shapes.h"
#include "Physics.h"
#include "Utils.h"
#include "Context.h"
#include "Texture.h"


class Player{
	public:
		Rectangle hitbox;
		PhysicsComponent physics;
		TextureID mc; 

		int state;
		bool charge;
		
		void collision(std::vector<Rectangle> level);
		void impulseResolution();
		void integration();

		void render();

		Player(int r, int c);
		~Player();
};
