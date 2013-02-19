#include "tileselector.h"

void TileSelector::initialize(int num, int width, int height, int currentLayer){

	_width = width;
	_height = height;

	tileset.tileSet(textures[currentLayer][num], width, height);

	textureArea.left = TEXTUREPOSX;
	textureArea.width = textures[currentLayer][num].getSize().x;
	textureArea.top = 0;
	textureArea.height = textures[currentLayer][num].getSize().y;

	selectedSprite.setTexture(textures[currentLayer][num]);
	selectedSprite.setTextureRect(tileset.getTileSet(0));

	for(int i=0;i<tileset.getTileNum();i++){
		tmpRect.left = tileset.getTileSet(i).left + TEXTUREPOSX;
		tmpRect.width = width;
		tmpRect.height = height;
		tmpRect.top = tileset.getTileSet(i).top;
		tiles.push_back(tmpRect);
	}

}

void TileSelector::setTexture(int num, int width, int height, int currentLayer){

	tiles.clear();

	_width = width;
	_height = height;

	tileset.tileSet(textures[currentLayer][num], width, height);

	textureArea.left = TEXTUREPOSX;
	textureArea.width = textures[currentLayer][num].getSize().x;
	textureArea.top = 0;
	textureArea.height = textures[currentLayer][num].getSize().y;

	selectedSprite.setTexture(textures[currentLayer][num]);
	selectedSprite.setTextureRect(tileset.getTileSet(0));

	for(int i=0;i<tileset.getTileNum();i++){
		tmpRect.left = tileset.getTileSet(i).left + TEXTUREPOSX;
		tmpRect.width = width;
		tmpRect.height = height;
		tmpRect.top = tileset.getTileSet(i).top;
		tiles.push_back(tmpRect);
	}
}

void TileSelector::select(int x, int y, sf::Event &event){

	for(i=0;i<=tiles.size();i++){
		if(tiles[i].contains(x, y))
			break;
	}

	selectedSprite.setPosition(x - (_width/2), y - (_height/2));

	if(mouseRight && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right && textureArea.contains(x, y)){
		selectedSprite.setTextureRect(tileset.getTileSet(i));	
		mouseRight = false;
	}
	if(!mouseRight && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
		mouseRight = true;

}

sf::IntRect TileSelector::getSelectedTile(){
	return selectedSprite.getTextureRect();
}

void TileSelector::draw(sf::RenderWindow &window){
	window.draw(selectedSprite);
}