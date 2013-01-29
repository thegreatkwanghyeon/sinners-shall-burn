#include "tooltip.h"

Tooltip::Tooltip(sf::String _path) : tooltipWidth(300), tooltipHeight(300){
	tileset = new TileSet();
	texture.loadFromFile(_path);

	individualTextureWidth = texture.getSize().x/3;
	individualTextureHeight = texture.getSize().y/3; //3X3 = 9등분 하기 위한것 

	texture = tileset->tileSet(_path, individualTextureWidth, individualTextureHeight); 

	for(int i=0; i<9; i++){
		sprite[i].setTexture(texture);
		sprite[i].setTextureRect(tileset->getTileSet(i));
	}

	font.loadFromFile("font/spike.ttf");
}

void Tooltip::defineSpriteScales(){

	sprite[Top].setScale(((float)tooltipWidth/individualTextureWidth),1);
	sprite[Left].setScale(1,((float)tooltipHeight/individualTextureHeight));
	sprite[Center].setScale(((float)tooltipWidth/individualTextureWidth),((float)tooltipHeight/individualTextureHeight));
	sprite[Right].setScale(1,((float)tooltipHeight/individualTextureHeight));
	sprite[Bottom].setScale(((float)tooltipWidth/individualTextureWidth),1);
}

void Tooltip::defineSpritePositions(){
	position = mousePosition;

	sprite[TopLeft].setPosition(position.x, position.y-(2*individualTextureHeight)-tooltipHeight);
	sprite[Top].setPosition(position.x+individualTextureWidth,position.y-(2*individualTextureHeight)-tooltipHeight);
	sprite[TopRight].setPosition(position.x+individualTextureWidth+tooltipWidth, position.y-(2*individualTextureHeight)-tooltipHeight);

	sprite[Left].setPosition(position.x, position.y- tooltipHeight- individualTextureHeight);
	sprite[Center].setPosition(position.x+individualTextureWidth, position.y- tooltipHeight- individualTextureHeight);
	sprite[Right].setPosition(position.x+individualTextureWidth+tooltipWidth, position.y- tooltipHeight- individualTextureHeight);

	sprite[BottomLeft].setPosition(position.x, position.y-individualTextureHeight);
	sprite[Bottom].setPosition(position.x+individualTextureWidth, position.y-individualTextureHeight);
	sprite[BottomRight].setPosition(position.x+individualTextureWidth+tooltipWidth, position.y-individualTextureHeight);

	title.setPosition(sprite[Center].getPosition());
	description.setPosition(sprite[Center].getPosition().x, sprite[Center].getPosition().y+title.getLocalBounds().height);
}

void Tooltip::setTitle(sf::String _stringTitle){
	title.setString(_stringTitle);
	title.setFont(font);

	tooltipWidth = title.getLocalBounds().width;
	tooltipHeight = title.getLocalBounds().height + description.getLocalBounds().height;
}

void Tooltip::setDescription(sf::String _stringDescription){
	description.setString(_stringDescription);
	description.setFont(font);
	description.setColor(sf::Color(200,200,200));
	description.setCharacterSize(14);

	tooltipWidth = title.getLocalBounds().width;
	tooltipHeight = title.getLocalBounds().height + description.getLocalBounds().height;

}

void Tooltip::setScope(sf::IntRect _rect){
	hoverRect = _rect;
}

void Tooltip::update(){
	defineSpriteScales();
	defineSpritePositions();
}

void Tooltip::draw(sf::RenderWindow &window){
	mousePosition = sf::Mouse::getPosition(window);

	if(hoverRect.contains(mousePosition)){
		for(int i=0; i<9; i++){
			window.draw(sprite[i]);
		}
		window.draw(title);
		window.draw(description);
	}

}