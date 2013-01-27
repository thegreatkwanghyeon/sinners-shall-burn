#include "titlescene.h"

TitleScene::TitleScene(){
	puzzle = new Puzzle();

	font.loadFromFile("font/font.ttf");
	text.setFont(font);
	text.setString("ihihihihihihi\nNum1 : titlescene+Puzzle\nNum2 : gamescene");
	text.setPosition(450.0f, 250.0f);

}

TitleScene::~TitleScene(){

}

void TitleScene::update(){

}

void TitleScene::draw(sf::RenderWindow &window){
	puzzle->draw(window);
	window.draw(text);
}