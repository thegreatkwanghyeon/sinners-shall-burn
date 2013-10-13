#include "pdata.h"

PData::PData(int _x, int _y){
	animation=new Animation();
	sprite.setPosition(_x, _y);
	x=_x;
	y=_y;
	animation->addTile("img/PuzzleAnimation.PNG",PBlockSize,PBlockSize);
	animation->setSpeed(0.2);
	animation->setTileRange(sf::Vector2i(1,1), 4);//����Ʈ.
	is_click=false;
	is_break=false;
}

void PData::init_animation(){
	if(is_break == true){
		animation->setSpeed(0.1);
		animation->setTileRange(sf::Vector2i(5,5),4);
	}else if(is_click == true){
		animation->setSpeed(0.2);
		animation->setTileRange(sf::Vector2i(1,5),4);
	}else{
		animation->setSpeed(0.2);
		switch(num){
			case -1 : animation->setTileRange(sf::Vector2i(5,4),4);break; //�� ���� ǥ�ÿ�.
			case 0 : animation->setTileRange(sf::Vector2i(1,1),4);break;
			case 1 : animation->setTileRange(sf::Vector2i(1,2),4);break;
			case 2 : animation->setTileRange(sf::Vector2i(1,3),4);break;
			case 3 : animation->setTileRange(sf::Vector2i(1,4),4);break;
			case 4 : animation->setTileRange(sf::Vector2i(5,1),4);break;
			case 5 : animation->setTileRange(sf::Vector2i(5,2),4);break;
			case 6 : animation->setTileRange(sf::Vector2i(5,3),4);break;
			default : animation->setTileRange(sf::Vector2i(5,4),4);
		}
	}
}
void PData::update(){
	animation->update(&sprite, true);
}
void PData::draw(sf::RenderWindow &window){//�ƹ����� ���� �� ĭ�� �ִϸ��̼� ���� �� ĭ�� �˾Ƽ� �ϸ� ��������� ���Ƽ� �غ�.
	window.draw(sprite);
}
int PData::getLocation(){
	return animation->getLocation();
}
void PData::init_position(int _x, int _y){
	sprite.setPosition((float)_x, (float)_y);
	x=_x;
	y=_y;
}