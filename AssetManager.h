#pragma once

#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H
#include <map>
#include <vector>
#include "Context.h"
#include "Utils.h"

extern std::map<std::string, SDL_Texture*> GraphicsManager; 
//font manager
extern std::map<std::string, TTF_Font*> FontsManager;
//music manager
extern std::map<std::string, Mix_Music*> MusicManager;
extern std::map<std::string, Mix_Chunk*> SoundEffectsManager;

bool insertTexture(std::string name, std::string filepath);
bool insertTexture(std::string name, std::string filepath, SDL_Rect* fill);
SDL_Texture* queryTexture(std::string name);
void printTextureDimensions(std::string name);
void removeTexture(std::string name);
void closeGraphicsManager();

bool insertMusic(std::string name , std::string filepath);
Mix_Music* queryMusic(std::string name);
void removeMusic(std::string name);
void closeMusicManager();

bool insertSoundEffect(std::string name, std::string filepath);
Mix_Chunk* querySoundEffect(std::string name);
void removeSoundEffect(std::string name);
void closeSoundEffectsManager();

/** ex. "helvetica" "file/to/helvetica.ttf" "12" will set "helvetica_12" int the font manager */
bool insertFont(std::string name, std::string filepath,int size);
TTF_Font* queryFont(std::string name);
void removeFont(std::string name);
void closeFontsManager();

void createTextureFromFont(std::string name, std::string nameOfFont, std::string text);

void closeManagers();


#endif // !_ASSETMANAGER_H

