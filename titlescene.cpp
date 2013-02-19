#include "titlescene.h"

TitleScene::TitleScene(){
	font.loadFromFile("font/spike.ttf");
	text.setFont(font);
	text.setString(L"num1 : 타이틀 씬 \nnum2 : 께임씬 \nnum3 : 셰이더씬\nnum4 : 퍼즐");
	text.setPosition(450.0f, 250.0f);

}
TitleScene::~TitleScene(){
	
}
void TitleScene::update(){
}

void TitleScene::draw(sf::RenderWindow &window){
	window.draw(text);
}