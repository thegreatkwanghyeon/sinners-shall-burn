#include "button.h"

Button::Button(sf::String _path) : isButtonEnable(true) {
	tileset = new TileSet();
	texture.loadFromFile(_path);
	font.loadFromFile("font/spike.ttf");
	texture = tileset->tileSet(_path, texture.getSize().x, (texture.getSize().y)/4);
	sprite.setTexture(texture);
	sprite.setTextureRect(tileset->getTileSet(NormalState));

}

void Button::setPosition(int _x, int _y){
	//이건 걍 버튼 이미지의 위치와 사이즈를 잡는것 신경 ㄴㄴ해 
	position = sf::Vector2i(_x,_y);
	buttonRect = sf::IntRect(position, sf::Vector2i(texture.getSize().x, texture.getSize().y/4));
	sprite.setPosition(_x, _y);
}

void Button::setText(sf::String _name, unsigned int _size){ //_size 에 값을 안주면 14로 지정
	buttonName.setFont(font);
	buttonName.setString(_name);
	buttonName.setCharacterSize(_size);
	buttonName.setPosition(position.x + texture.getSize().x / 2 - buttonName.getLocalBounds().width/2,position.y + texture.getSize().y / 8 - buttonName.getLocalBounds().height);

}

bool Button::isMouseOver(sf::Vector2i _mousePosition){
	//buttonRect 범위 안에 _mousePosition 이 있는가
	return buttonRect.contains(_mousePosition);
}

bool Button::isMouseClicked(){
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}



void Button::update(){
	if(!isButtonEnable){ 
		sprite.setTextureRect(tileset->getTileSet(DisableState));
	}else if(isMouseOver(mousePosition) && isButtonEnable){
		if(isMouseClicked()){
			sprite.setTextureRect(tileset->getTileSet(ClickedState));
		}else{
			sprite.setTextureRect(tileset->getTileSet(HoverState));
		}
	}else{
		sprite.setTextureRect(tileset->getTileSet(NormalState));
	}
}

void Button::draw(sf::RenderWindow &window){
	mousePosition = sf::Mouse::getPosition(window);
	window.draw(sprite);
	window.draw(buttonName);
}


bool Button::checkMouseClick(){
	if(isMouseOver(mousePosition) && isMouseClicked() && isButtonEnable){
		return true;
	}else{
		return false;
	}
}


void Button::enableButton(){
	isButtonEnable = true;
}
void Button::disableButton(){
	isButtonEnable = false;
}