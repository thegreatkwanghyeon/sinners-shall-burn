#include "titleScreen.h"

TitleScreen::TitleScreen(){

}

void TitleScreen::loadContent(){
	///테스트용 텍스트 띄우기 (추후 삭제 바람)
	font.loadFromFile("font.ttf");
	text.setString("Title");
	text.setFont(font);


	//실제 load 부분
	character.loadContent();
	character.setPosition(0.0f, 0.0f);


}

void TitleScreen::unloadContent(){
	character.unloadContent();
}

void TitleScreen::update(){
	character.update();

}

void TitleScreen::draw(sf::RenderWindow &window){
	window.draw(text);
	character.draw(window);
	
}

