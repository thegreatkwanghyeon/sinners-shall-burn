#include "titlescene.h"

TitleScene::TitleScene(){
	puzzle = new Puzzle();

	font.loadFromFile("font/spike.ttf");
	text.setFont(font);
	text.setString(L"ihihihihihihi\nNum1 : titlescene+Puzzle\nNum2 : gamescene\n 안녕");
	text.setPosition(450.0f, 250.0f);

}

TitleScene::~TitleScene(){

}

void TitleScene::update(){
	puzzle->update();
}

void TitleScene::draw(sf::RenderWindow &window){
	puzzle->draw(window);
	window.draw(text);
}