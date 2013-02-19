#include "global.h"

sf::Texture textures[2][50];
std::string texturePaths[2][50];

bool mouseLeft = true, mouseRight = true;

void initialize(){

	texturePaths[0][0] = "tiles/green.png";
	texturePaths[0][1] = "tiles/red.png";

//---------------------------------------------------------------------------------------	

	texturePaths[1][0] = "tiles/tree.png";

//---------------------------------------------------------------------------------------

	textures[0][0].loadFromFile(texturePaths[0][0]);
	textures[0][1].loadFromFile(texturePaths[0][1]);

//---------------------------------------------------------------------------------------	

	textures[1][0].loadFromFile(texturePaths[1][0]);	
}