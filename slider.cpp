#include "slider.h"

Slider::Slider(float *value, String tileSetPath, String handlePath){
	tileSet = new TileSet();

	tileSetTexture.loadFromFile(tileSetPath);
	tileSetTexture = tileSet->tileSet(tileSetPath, tileSetTexture.getSize().x, tileSetTexture.getSize().y / 2);

	baseSprite.setTexture(tileSetTexture);
	baseSprite.setTextureRect(tileSet->getTileSet(0));

	middleSprite.setTexture(tileSetTexture);
	middleSprite.setTextureRect(tileSet->getTileSet(1));

	IntRect tmpTextureRect = middleSprite.getTextureRect();
	tmpTextureRect.width = 0;
	middleSprite.setTextureRect(tmpTextureRect);

	handleTexture.loadFromFile(handlePath);

	handleSprite.setTexture(handleTexture);

	controllable = false;

	this->value = value;
}

float Slider::getPercentage(){
	return relativeMousePositionX / baseSprite.getGlobalBounds().width * 100;
}

void Slider::setHandlePosition(){
	handleSprite.setPosition(baseSprite.getPosition().x + relativeMousePositionX - handleSprite.getGlobalBounds().width/2, handleSprite.getPosition().y);
}

void Slider::setLimit(float limit){
	this->limit = limit;
	handleSprite.setPosition(baseSprite.getPosition().x + (baseSprite.getGlobalBounds().width * (*value) / limit) - handleSprite.getGlobalBounds().width / 2, handleSprite.getPosition().y);
	IntRect tmpTextureRect = middleSprite.getTextureRect();
	tmpTextureRect.width = baseSprite.getGlobalBounds().width * (*value) / limit;
	middleSprite.setTextureRect(tmpTextureRect);
}

void Slider::setValue(){
	*value = (getPercentage() / 100) * limit;
}

void Slider::update(){

	if (Mouse::isButtonPressed(Mouse::Left)){
		if (!controllable && baseSprite.getGlobalBounds().contains((Vector2f)mousePosition)){
			controllable = true;
		}
	}
	else{
		if (controllable){
			controllable = false;
		}
	}

	if (controllable){
			if (relativeMousePositionX < 0){
				relativeMousePositionX = 0;
			}
			else if (relativeMousePositionX > baseSprite.getGlobalBounds().width){
				relativeMousePositionX = baseSprite.getGlobalBounds().width;
			}

			setHandlePosition();
			setValue();

			IntRect tmpTextureRect = middleSprite.getTextureRect();
			tmpTextureRect.width = relativeMousePositionX;
			middleSprite.setTextureRect(tmpTextureRect);
	}
}

void Slider::draw(RenderWindow &window){
	mousePosition = Mouse::getPosition(window);

	relativeMousePositionX = mousePosition.x - baseSprite.getPosition().x;

	window.draw(baseSprite);
	window.draw(middleSprite);
	window.draw(handleSprite);
}

void Slider::setPosition(int x, int y){
	baseSprite.setPosition(x, y);
	middleSprite.setPosition(x, y);
	handlePositionY = y - (handleSprite.getGlobalBounds().height / 2 - baseSprite.getGlobalBounds().height / 2);
	handleSprite.setPosition(x - handleSprite.getGlobalBounds().width/2, handlePositionY);
}
