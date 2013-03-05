#include "gamescene.h"
#include "stdio.h"

GameScene::GameScene(){
	//character = new Character(0.0f, 0.0f);
	map = new Map();
	map->initialize();
	map->load("test");
	uiscene = new UiScene();
	player = new Player("img/male_walkcycle.png", sf::Vector2i(80.0f, 90.0f));


}

void GameScene::update(sf::Event &event){
	//character->update();
	uiscene->update(event);
	player->update(map->getCollideRects());
}

void GameScene::draw(sf::RenderWindow &window){
	map->ground_Draw(window);
	//character->draw(window);
	player->draw(window);
	map->object_Draw(window);
	uiscene->draw(window);
	

}