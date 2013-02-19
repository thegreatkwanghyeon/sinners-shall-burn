#include "titlescene.h"

TitleScene::TitleScene(){
	puzzle = new Puzzle();

	font.loadFromFile("font/spike.ttf");
	text.setFont(font);
	text.setString(L"num1 : 타이틀 씬 \nnum2 : 께임씬 \nnum3 : 셰이더씬");
	text.setPosition(450.0f, 250.0f);

}

TitleScene::~TitleScene(){
	delete puzzle;
}

void TitleScene::update(){
	puzzle->update();
}

void TitleScene::draw(sf::RenderWindow &window){
	puzzle->draw(window);
	window.draw(text);
}