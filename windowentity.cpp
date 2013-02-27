#include "windowentity.h"

WindowEntity::WindowEntity(const char *_path) : tooltipHeight(30), tooltipWidth(30){
	tileset = new TileSet();
	position = sf::Vector2f(410.0f, 410.0f);

	texture.loadFromFile(_path);
	
	individualTextureWidth = texture.getSize().x/3;
	individualTextureHeight = texture.getSize().y/3; //3X3 = 9등분 하기 위한것 
	
	texture = tileset->tileSet(_path, individualTextureWidth, individualTextureHeight); 

	for(int i=0; i<9; i++){
		sprite[i].setTexture(texture);
		sprite[i].setTextureRect(tileset->getTileSet(i));
	}
}

void WindowEntity::defineSpriteScales(){ //텍스트 양에 따라서 스프라이트 크기 조절해준다 신경 ㄴㄴ 

	sprite[Top].setScale(((float)tooltipWidth/individualTextureWidth),1);
	sprite[Left].setScale(1,((float)tooltipHeight/individualTextureHeight));
	sprite[Center].setScale(((float)tooltipWidth/individualTextureWidth),((float)tooltipHeight/individualTextureHeight));
	sprite[Right].setScale(1,((float)tooltipHeight/individualTextureHeight));
	sprite[Bottom].setScale(((float)tooltipWidth/individualTextureWidth),1);
}

void WindowEntity::defineSpritePositions(){ //9등분한 스프라이트 위치 재배치 신경 ㄴㄴ

	sprite[TopLeft].setPosition(position.x, position.y-(2*individualTextureHeight)-tooltipHeight);
	sprite[Top].setPosition(position.x+individualTextureWidth,position.y-(2*individualTextureHeight)-tooltipHeight);
	sprite[TopRight].setPosition(position.x+individualTextureWidth+tooltipWidth, position.y-(2*individualTextureHeight)-tooltipHeight);

	sprite[Left].setPosition(position.x, position.y- tooltipHeight- individualTextureHeight);
	sprite[Center].setPosition(position.x+individualTextureWidth, position.y- tooltipHeight- individualTextureHeight);
	sprite[Right].setPosition(position.x+individualTextureWidth+tooltipWidth, position.y- tooltipHeight- individualTextureHeight);

	sprite[BottomLeft].setPosition(position.x, position.y-individualTextureHeight);
	sprite[Bottom].setPosition(position.x+individualTextureWidth, position.y-individualTextureHeight);
	sprite[BottomRight].setPosition(position.x+individualTextureWidth+tooltipWidth, position.y-individualTextureHeight);
}

void WindowEntity::setPosition(sf::Vector2f _position){
	position = _position;
}

void WindowEntity::setWindowSize(float _width, float _height){
	tooltipWidth = _width;
	tooltipHeight = _height;

}

void WindowEntity::update(){
	defineSpriteScales();
	defineSpritePositions();
}

void WindowEntity::draw(sf::RenderWindow &window){
	for(int i=0; i<9; i++){
		window.draw(sprite[i]);
	}
}