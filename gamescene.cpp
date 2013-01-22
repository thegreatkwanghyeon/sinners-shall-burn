#include "gamescene.h"
#include "stdio.h"

GameScene::GameScene(){
	character = new Character(100.0f, 100.0f);
	map = new Map("img/map.jpg");
}

void GameScene::update(){
	character->update();
}

void GameScene::draw(sf::RenderWindow &window){
	map->draw(window);
	character->draw(window);
}