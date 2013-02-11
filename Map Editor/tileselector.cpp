#include "tileselector.h"

void TileSelector::initialize(sf::Texture mainTexture){

	tileset.tileSet(mainTexture, TILEWIDTH, TILEHEIGHT);
	tmpTexture = mainTexture ;

	textureArea.left = TEXTUREPOSX;
	textureArea.width = tmpTexture.getSize().x;
	textureArea.top = 0;
	textureArea.height = tmpTexture.getSize().y;

	selectedSprite.setTexture(tmpTexture);
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