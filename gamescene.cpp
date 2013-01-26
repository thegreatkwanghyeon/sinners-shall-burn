#include "gamescene.h"
#include "stdio.h"

GameScene::GameScene(){
	character = new Character(100.0f, 100.0f);
	map = new Map("img/map.jpg");

	button = new Button("img/button.png");
	button2 = new Button("img/button.png");
	button->setPosition(300,300);
	button->setText("Enabler", 18);
	button2->setPosition(300,380);
	button2->setText("Click me if you can");
	button2->disableButton();
}

void GameScene::update(){
	character->update();

	button->update();
	button2->update();
	if(button->checkMouseClick()){
		button2->enableButton();
	}
}

void GameScene::draw(sf::RenderWindow &window){
	map->draw(window);
	character->draw(window);

	button->draw(window);
	button2->draw(window);
	
	
}