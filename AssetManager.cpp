#include "AssetManager.h"


std::map<std::string, SDL_Texture*> GraphicsManager;
std::map<std::string, std::string> FontManager;

bool insertTexture(std::string name, std::string filename) {

	SDL_Texture* query = NULL;
		//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(filename.c_str());

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), IMG_GetError());
		return false;
	}
	else
	{
		//Create texture from surface pixels
		query = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		if (query == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", filename.c_str(), SDL_GetError());
			return false;
		}
		else{

			GraphicsManager[name] = query;
			return true;

		}

	}

}

void removeTexture(std::string name) {
	SDL_DestroyTexture(GraphicsManager[name]);
	GraphicsManager[name] = NULL;
	GraphicsManager.erase(name);
}

SDL_Texture* queryTexture(std::string name) {
	SDL_Texture* query = GraphicsManager[name];
	return query;

}

void printTextureDimensions(std::string name) {
	SDL_Texture* query = GraphicsManager[name];
	SDL_Rect temp;
	SDL_QueryTexture(query, NULL, NULL, &temp.w, &temp.h);
	if (query == NULL) {
		printf("%s : FAILED TO QUERY! \n", name.c_str());
	}
	else {
		printf("%s texture has dimensions [%d, %d] \n", temp.w, temp.h);
	}
}


