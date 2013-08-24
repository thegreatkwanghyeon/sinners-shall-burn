#include "gamescene.h"
#include "stdio.h"

GameScene::GameScene(){
	rayCastingScene = new RayCastingScene();
	player = new Player();
	battle = new Battle(1,player);

	isBattle=false;
}

void GameScene::update(sf::Event &event){
	int temp;
	if(!isBattle)//전투시엔 이동 등을 막고 그림만 배경으로 출력해줌^^
		rayCastingScene->update(event);
	battle->update(event);

	temp=rayCastingScene->isBattle();
	if(temp != -1){
		isBattle=true;
		battle->startBattle(temp);
	}

	if(battle->getResult() != 0){
		isBattle=false;
	}
}

void GameScene::draw(sf::RenderWindow &window){
	rayCastingScene->draw(window);
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 1280, 700));

	view.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
	window.setView(view);
	battle->draw(window);
	view.setViewport(sf::FloatRect(0.f, 0.f, 2.0f, 2.0f));
	window.setView(view);
}