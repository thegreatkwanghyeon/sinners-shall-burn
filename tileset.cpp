#include "tileset.h"
#include <stdio.h>

sf::Texture TileSet::tileSet(std::string path, sf::Vector2i tileSize){
	temp = 0;

	texture.loadFromFile(path);

	_tileSize = tileSize;

	for(unsigned int i = 0; i <= texture.getSize().y/tileSize.y-1; i++){
		for(unsigned int j = 0; j <= texture.getSize().x/tileSize.x-1; j++){
			tmpcoord.x = j * tileSize.x;
			tmpcoord.y = i * tileSize.y;
			coords.push_back(tmpcoord);
			printf("%d(%d) : %d, %d\n", temp, coords[temp].x, coords[temp].y);
			temp ++;
		}
	}
	printf("number of tiles%d\n", temp);
	return texture;
}

sf::IntRect TileSet::getTileSet(int tileNum){
	
	tileRect.left = coords[tileNum].x;
	tileRect.width = _tileSize.x;
	tileRect.top = coords[tileNum].y;
	tileRect.height = _tileSize.y;

	return tileRect;
}