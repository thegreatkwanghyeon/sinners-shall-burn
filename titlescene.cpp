#include "titlescene.h"

TitleScene::TitleScene(){
	font.loadFromFile("font/spike.ttf");
	text.setFont(font);
	text.setString(L"num1 : ≈∏¿Ã∆≤ æ¿ \nnum2 : ≤≤¿”æ¿ \nnum3 : ºŒ¿Ã¥ıæ¿\nnum4 : ∆€¡Ò");
	text.setPosition(450.0f, 250.0f);

}
TitleScene::~TitleScene(){
	
}
void TitleScene::update(){
}

void TitleScene::draw(sf::RenderWindow &window){
	window.draw(text);
}