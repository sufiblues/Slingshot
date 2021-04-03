#include "Player.h"

Player::Player(int r, int c){
	insertTexture("chars", "assets/textures/char_test/idle0001.png");
  setTextureID(&mc, "chars");
      
}

void Player::collision(std::vector<Rectangle> level){
  int res = 0;
  for (int i = 0; i<level.size(); i++){
    if (!res){
      res = collisionRectangleAndRectangle(&hitbox, &level[i]);
      break;
    }
  }
  
  if (res){
    printf("Found collision!\n");
  }

}
