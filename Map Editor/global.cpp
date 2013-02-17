#include "global.h"

sf::Texture textures[50];
std::string texturePaths[50];

void initialize(){

	texturePaths[0] = "tiles/green.png";
	texturePaths[1] = "tiles/red.png";

	textures[0].loadFromFile(texturePaths[0]);
	textures[1].loadFromFile(texturePaths[1]);
}