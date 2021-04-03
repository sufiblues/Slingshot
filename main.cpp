

#include <math.h>

#include "Context.h"
#include "Shapes.h"
#include "Physics.h"
#include "AssetManager.h"
#include "Texture.h"
#include "Controller.h"
#include "GameEngine.h"





int main(int argc, char* args[]) {

	  createContext();
    
    Rectangle a;
    Rectangle b;

    a.center = glm::vec2(20,20);
    a.width = 10;
    a.height = 15;

    b.center = glm::vec2(20, 20);
    b.width = 10;
    b.height = 5;

    printf("%d\n", collisionRectangleAndRectangle(&a, &b));
    //engineStart();
    
    destroyContext();
 
	return 0;
}
