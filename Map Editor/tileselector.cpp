#include "tileselector.h"

void TileSelector::initialize(int num){

	tileset.tileSet(textures[num], TILEWIDTH, TILEHEIGHT);

	textureArea.left = TEXTUREPOSX;
	textureArea.width = textures[num].getSize().x;
	textureArea.top = 0;
	textureArea.height = textures[num].getSize().y;

	selectedSprite.setTexture(textures[num]);
	selectedSprite.setTextureRect(tileset.getTileSet(0));

	for(int i=0;i<tileset.getTileNum();i++){
		tmpRect.left = tileset.getTileSet(i).left + TEXTUREPOSX;
		tmpRect.width = TILEWIDTH;
		tmpRect.height = TILEHEIGHT;
		tmpRect.top = tileset.getTileSet(i).top;
		tiles.push_back(tmpRect);
	}

}

void TileSelector::select(int x, int y){

	for(i=0;i<=tiles.size();i++){
		if(tiles[i].contains(x, y))
			break;
	}

	selectedSprite.setPosition(x - TILEWIDTH/2, y - TILEHEIGHT/2);

	if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && textureArea.contains(x, y))
		selectedSprite.setTextureRect(tileset.getTileSet(i));	
}

sf::IntRect TileSelector::getSelectedTile(){
	return selectedSprite.getTextureRect();
}

void TileSelector::draw(sf::RenderWindow &window){
	window.draw(selectedSprite);
}