#ifndef __global__
#define __global__

#include <stdio.h>
#include "stdafx.h"
#define MAPWIDTH 800
#define MAPHEIGHT 600
#define TILEWIDTH 40
#define TILEHEIGHT 40
#define TEXTUREPOSX 800 + 10
#define MAXTEXTURES 2

extern sf::Texture textures[50];

extern std::string texturePaths[50];

extern void initialize();

extern bool mouseLeft, mouseRight;

struct TILE{
	sf::Sprite sprite;
	std::string string;
};

#endif