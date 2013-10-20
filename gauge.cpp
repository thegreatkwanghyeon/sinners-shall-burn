#include "gauge.h"

Gauge::Gauge(sf::String _path, float _limit, int _gaugeType, int _textPercentage){
	tileset = new TileSet();
	texture.loadFromFile(_path);
	font.loadFromFile("font/spike.ttf");
	texture = tileset->tileSet(_path, texture.getSize().x, (texture.getSize().y)/3);

	coverSprite.setTexture(texture);
	coverSprite.setTextureRect(tileset->getTileSet(0));

	middleSprite.setTexture(texture);
	middleSprite.setTextureRect(tileset->getTileSet(1));

	baseSprite.setTexture(texture);
	baseSprite.setTextureRect(tileset->getTileSet(2));

	gaugeLimit = _limit;
	gaugeValue = _limit;
	gaugeType = _gaugeType;
	textPercentage = _textPercentage;

}

void Gauge::setGaugeTextureRect(){
	sf::IntRect tmpRect;
	float tmpTextureSize = texture.getSize().y/3;
	tmpRect = middleSprite.getTextureRect();
	if(gaugeType == 0){ //가로형 게이지일 경우 
		tmpRect.width = (int)(texture.getSize().x * (gaugeValue / gaugeLimit));
	}
	else if(gaugeType == 1){ //세로형 게이지일 경우
		tmpRect.top = (int)(tmpTextureSize * ((gaugeLimit*2) - gaugeValue) / gaugeLimit);
		tmpRect.height = (int)(tmpTextureSize*gaugeValue/gaugeLimit);
		middleSprite.setPosition(position.x, position.y + tmpTextureSize*(gaugeLimit - gaugeValue)/gaugeLimit);
	}
	middleSprite.setTextureRect(tmpRect);

}

void Gauge::setText(){

	char tmpBuffer[100]; 
	if(textPercentage == 0){ //텍스트를 퍼센트로 표현하지 않으면
		_snprintf(tmpBuffer, sizeof(tmpBuffer), "%.0f / %.0f", gaugeValue, gaugeLimit);
	}else if(textPercentage == 1){ //텍스트를 퍼센트로 표현하면 
		_snprintf(tmpBuffer, sizeof(tmpBuffer), "%.0f%%", gaugeValue / gaugeLimit * 100);
	}else{//텍스트 출력을 원치 않는 경우
		_snprintf(tmpBuffer, sizeof(tmpBuffer), "");
	}
	text.setFont(font);
	text.setString(tmpBuffer);
	text.setPosition(position.x + texture.getSize().x / 2 - text.getLocalBounds().width/2,position.y + texture.getSize().y / 6 - text.getLocalBounds().height/2);
}

void Gauge::setValue(float _value){
	if((gaugeValue + _value) <= gaugeLimit && (gaugeValue + _value) >= 0)
		gaugeValue += _value;
}

void Gauge::setPosition(sf::Vector2i _position){
	position = _position;
	middleSprite.setPosition(_position.x, _position.y);
	baseSprite.setPosition(_position.x, _position.y);
	coverSprite.setPosition(_position.x, _position.y);
}

void Gauge::setTextElement(int _textSize, sf::Color _textColor){
	text.setCharacterSize(_textSize);
	text.setColor(_textColor);
}

void Gauge::update(){
	setText();
	setGaugeTextureRect();
}

void Gauge::draw(sf::RenderWindow &window){
	window.draw(baseSprite);
	window.draw(middleSprite);
	window.draw(coverSprite);
	window.draw(text);
}
float Gauge::getValue(){
	return gaugeValue;
}