#include "tileset.h"
#include <stdio.h>

sf::Texture TileSet::tileSet(std::string path, int _tileSizeX, int _tileSizeY){
	temp = 0;

	texture.loadFromFile(path);

	tileSizeX = _tileSizeX;
	tileSizeY = _tileSizeY;

	for(unsigned int i = 0; i <= texture.getSize().y/tileSizeY-1; i++){
		for(unsigned int j = 0; j <= texture.getSize().x/tileSizeX-1; j++){
			tmpcoord.x = j * tileSizeX;
			tmpcoord.y = i * tileSizeY;
			coords.push_back(tmpcoord);
			//printf("%d : %d, %d\n", temp, coords[temp].x, coords[temp].y); 
			temp ++;
		}
	}
	//printf("number of tiles%d\n", temp);
	return texture;
}

sf::IntRect TileSet::getTileSet(int tileNum){
	
	tileRect.left = coords[tileNum].x;
	tileRect.width = tileSizeX;
	tileRect.top = coords[tileNum].y;
	tileRect.height = tileSizeY;

	return tileRect;
}