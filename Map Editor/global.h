#ifndef __global__
#define __global__

#include <stdio.h>
#include <SFML/Graphics.hpp>
#define MAPWIDTH 800
#define MAPHEIGHT 600
#define MAPTILEWIDTH 40
#define MAPTILEHEIGHT 40
#define OBJECTTILEWIDTH 80
#define OBJECTTILEHEIGHT 120
#define TEXTUREPOSX 800 + 10
#define MAXMAPTEXTURES 2
#define MAXOBJECTTEXTURES 1

extern sf::Texture textures[2][50];

extern std::string texturePaths[2][50];

extern void initialize();

extern bool mouseLeft, mouseRight;

struct TILE{
	sf::Sprite sprite;
	std::string string;
};

#endif