#include "menuScreen.h"

MenuScreen::MenuScreen(){

}

void MenuScreen::loadContent(){
	font.loadFromFile("font.ttf");

	text.setString("Menu");
	text.setFont(font);
}

void MenuScreen::unloadContent(){

}

void MenuScreen::update(){


}

void MenuScreen::draw(sf::RenderWindow &window){
	window.draw(text);
}

