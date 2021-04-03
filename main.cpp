

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
    engineStart();
    
    destroyContext();
 
	return 0;
}
