#include "dialog.h"

Dialog::Dialog(const char *_path) : WindowEntity(_path){
}

void Dialog::update(){
	WindowEntity::update();
}

void Dialog::draw(sf::RenderWindow &window){
	WindowEntity::draw(window);
}