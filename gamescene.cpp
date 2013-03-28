#include "gamescene.h"
#include "stdio.h"

GameScene::GameScene(){
	//character = new Character(0.0f, 0.0f);
	map = new Map();
	map->initialize();
	map->load("test");
	uiscene = new UiScene();
	player = new Player("img/male_walkcycle.png", sf::Vector2i(100.0f, 120.0f));

	button = new Button("img/button.png");
	button->setPosition(100,100);
	button->setText("Battle", 18);
	//button->setHotkey(sf::Keyboard::H);

	flag=false;
}

void GameScene::update(sf::Event &event){
	int tp;
	//character->update();
	if(flag == true){
		battle->update(event);
		tp=battle->GetResult();
		if(tp == -1){
			printf("lose");
			delete(battle);
			flag=false;
		}else if(tp == 1){
			printf("win");
			delete(battle);
			flag=false;
		}
	}else{
		uiscene->update(event);
		player->update(map->getCollideRects());
	}

	button->update();
	if(button->checkMouseClick() && flag == false){
		flag=true;
		battle=new Battle(1,player);
	}
}

void GameScene::draw(sf::RenderWindow &window){
	if(flag == true){
		battle->draw(window);
	}else{
		map->ground_Draw(window);
		//character->draw(window);
		if(map->isDepth(player->getSprite()))
			player->draw(window);
		map->object_Draw(window);
		if(!map->isDepth(player->getSprite()))
			player->draw(window);
		uiscene->draw(window);
		button->draw(window);
	}	
}