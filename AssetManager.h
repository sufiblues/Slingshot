#pragma once

#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H

#include <map>
#include "Context.h"

extern std::map<std::string, SDL_Texture*> GraphicsManager; 
//ex. FontManager['helvetica', "path/to/helvetica-font"]
//todo
extern std::map<std::string, std::string> FontManager;

bool insertTexture(std::string name, std::string filepath);

SDL_Texture* queryTexture(std::string name);

void printTextureDimensions(std::string name);

void removeTexture(std::string name);


#endif // !_ASSETMANAGER_H

