#include "gamescene.h"
#include "stdio.h"

GameScene::GameScene(){
	character = new Character(0.0f, 0.0f);
	map = new Map("img/map.jpg");
	uiscene = new UiScene();
	player = new Player("img/male_walkcycle.png", sf::Vector2i(200.0f, 200.0f));


}

void GameScene::update(){
	character->update();
	uiscene->update();
	player->update();
}

void GameScene::draw(sf::RenderWindow &window){
	map->draw(window);
	character->draw(window);
	uiscene->draw(window);
	player->draw(window);

}