#include "tileset.h"

sf::Texture TileSet::tileSet(std::string path, sf::Vector2i tileSize){

	texture.loadFromFile(path);

	_tileSize = tileSize;

	for(unsigned int i = 0; i <= texture.getSize().x - tileSize.x; i += tileSize.x){
		for(unsigned int j = 0; j <= texture.getSize().y - tileSize.y; j += tileSize.y){
			tmpcoord.x = j;
			tmpcoord.y = i;
			coords.push_back(tmpcoord);
		}
	}

	return texture;
}

sf::IntRect TileSet::getTileSet(int tileNum){
	
	tileRect.left = coords[tileNum].x;
	tileRect.width = _tileSize.x;
	tileRect.top = coords[tileNum].y;
	tileRect.height = _tileSize.y;


	return tileRect;
}