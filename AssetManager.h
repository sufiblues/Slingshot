#pragma once

#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H

#include <map>
#include <vector>
#include "Context.h"

extern std::map<std::string, SDL_Texture*> GraphicsManager; 
//ex. FontManager['helvetica', "path/to/helvetica-font"]
//todo
extern std::map<std::string, std::string> FontManager;
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

void closeManagers();


#endif // !_ASSETMANAGER_H

