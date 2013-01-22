#include "titlescene.h"

TitleScene::TitleScene(){

	font.loadFromFile("font/font.ttf");
	text.setFont(font);
	text.setString("ihihihihihihi\nNum1 : titlescene\nNum2 : gamescene");
	text.setPosition(350.0f, 250.0f);

}

TitleScene::~TitleScene(){

}

void TitleScene::update(){

}

void TitleScene::draw(sf::RenderWindow &window){
	window.draw(text);
}