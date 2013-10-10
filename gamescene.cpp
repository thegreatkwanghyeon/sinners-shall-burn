#include "gamescene.h"
#include "stdio.h"

GameScene::GameScene(){
	rayCastingScene = new RayCastingScene();
	player = new Player();
	battle = new Battle(1,player);
	for(int i=0;i<1;i++){
		enemy.push_back(new Enemy(1));
	}

	pEnemy = &enemy; 

	texture.loadFromFile("img/textures/pillar.png");

	enemy[0]->setPosition(sf::Vector2f(3.5, 3.5));
	enemy[0]->setTexture(texture);

	rayCastingScene->setEnemies(pEnemy); //레이캐스팅 씬으로 넘겨줌

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
		battle->startBattle(enemy[temp]);
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