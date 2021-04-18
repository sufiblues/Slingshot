#include "AssetManager.h"


std::map<std::string, SDL_Texture*> GraphicsManager;
std::map<std::string, std::string> FontManager;
std::map<std::string, Mix_Music*> MusicManager;
std::map<std::string, Mix_Chunk*> SoundEffectsManager;

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


bool insertTexture(std::string name, std::string filename,SDL_Rect* fill) {

	SDL_Texture* query = NULL;
		//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(filename.c_str());
  SDL_Surface* destination = SDL_CreateRGBSurfaceWithFormat(0, fill->w,fill->h , 32, SDL_PIXELFORMAT_RGBA32);
	if (loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), IMG_GetError());
		return false;
	}
	else{
		SDL_BlitScaled(loadedSurface,NULL,destination, fill);
		if (destination == NULL){
				printf("Unable to scale surface %s! SDL Error: %s\n", filename.c_str(), SDL_GetError());
				return false;
		}
		//Create texture from surface pixels
		query = SDL_CreateTextureFromSurface(Renderer, destination);
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		SDL_FreeSurface(destination);
		if (query == NULL){
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

void closeGraphicsManager(){
	std::vector<std::string> key_names;
	for (auto const& pair:GraphicsManager ){
		key_names.push_back(pair.first);	
	}
	for (int i = 0; i < key_names.size(); i++){
  	removeTexture(key_names[i]);
	}

}

bool insertMusic(std::string name, std::string filepath){
	Mix_Music* mus = Mix_LoadMUS(filepath.c_str());
	
	if (mus == NULL){
		printf("Unable to load music %s! SDL_Mix Error: %s\n", filepath.c_str(), Mix_GetError());
		return false;
  }
	
	MusicManager[name] = mus;
	mus = NULL;
	return true;
}

Mix_Music* queryMusic(std::string name){
	Mix_Music* query = MusicManager[name];
	return query;
}

void removeMusic(std::string name){
	Mix_FreeMusic(MusicManager[name]);
	MusicManager[name] = NULL;
	MusicManager.erase(name);
}
//TODO finish implementing close functions for asset managers
void closeMusicManager(){
	
	std::vector<std::string> key_names;
	for (auto const& pair:MusicManager ){
		key_names.push_back(pair.first);	
	}
	for (int i = 0; i < key_names.size(); i++){
  	removeMusic(key_names[i]);
	}
}


bool insertSoundEffect(std::string name, std::string filepath){
	Mix_Chunk* loadedSound = Mix_LoadWAV(filepath.c_str());
	
	if (loadedSound == NULL){
		printf("Unable to load sound effect %s! SDL_Mix Error: %s\n", filepath.c_str(), Mix_GetError());
		return false;
  }
	
	SoundEffectsManager[name] = loadedSound;
	loadedSound = NULL;
	return true;
}

Mix_Chunk* querySoundEffect(std::string name){
	Mix_Chunk* query = SoundEffectsManager[name];
	return query;
}

void removeSoundEffect(std::string name){
	Mix_FreeChunk(SoundEffectsManager[name]);
	SoundEffectsManager[name] = NULL;
	SoundEffectsManager.erase(name);
}
//TODO finish implementing close functions for asset managers
void closeSoundEffectsManager(){	

	std::vector<std::string> key_names;
	for (auto const& pair:SoundEffectsManager ){
		key_names.push_back(pair.first);	
	}
	for (int i = 0; i < key_names.size(); i++){
  	removeSoundEffect(key_names[i]);
	}
}

void closeManagers(){
	closeGraphicsManager();
	closeMusicManager();
	closeSoundEffectsManager();
}

