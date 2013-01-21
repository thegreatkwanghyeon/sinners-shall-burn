#include "map.h"

Map::Map(std::string texturePath){
	mapTexture.loadFromFile(texturePath);
	sprite.setTexture(mapTexture);
}

void Map::draw(sf::RenderWindow &window){
	window.draw(sprite);
}
