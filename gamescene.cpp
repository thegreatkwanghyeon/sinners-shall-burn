#include "gamescene.h"
#include "stdio.h"

GameScene::GameScene(){
	rayCastingScene = new RayCastingScene();
	player = new Player();
	battle = new Battle(0,player);
}

void GameScene::update(sf::Event &event){
	rayCastingScene->update(event);
}

void GameScene::draw(sf::RenderWindow &window){
	rayCastingScene->draw(window);
}