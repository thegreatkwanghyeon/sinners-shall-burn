#ifndef __global__
#define __global__

#include <stdio.h>
#include <SFML/Graphics.hpp>
#define MAPWIDTH 800
#define MAPHEIGHT 600
#define TILEWIDTH 40
#define TILEHEIGHT 40
#define TEXTUREPOSX 800 + 10

struct TILE{
	sf::Sprite sprite;
	std::string string;
};

#endif