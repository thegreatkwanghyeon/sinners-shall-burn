#include "gamescene.h"
#include "stdio.h"

GameScene::GameScene(){
	rayCastingScene = new RayCastingScene();
	player = new Player();
	battle = new Battle(player);
	for(int i=0;i<1;i++){
		enemy.push_back(new Enemy(1));
	}

	pEnemy = &enemy; 

	texture.loadFromFile("img/textures/pillar.png");

	enemy[0]->setPosition(sf::Vector2f(3.5, 3.5));
	enemy[0]->setTexture(texture);

	rayCastingScene->setEnemies(pEnemy); //����ĳ���� ������ �Ѱ���

	isBattle=false;
	nowEnemy=0;
}

void GameScene::update(sf::Event &event){

	battle->update(event);

	if(isBattle){//����
		if(battle->getResult() != 0){//�������� ��, ������ ���������� �����ϴ� �Լ��̴�.
			isBattle=false;
			enemy.erase(enemy.begin()+nowEnemy);//���� ������ �� ����
		}
	}else{//������
		rayCastingScene->update(event);
		
		nowEnemy=rayCastingScene->isBattle();
		if(nowEnemy != -1){
			printf("[%d %d]",nowEnemy,enemy[nowEnemy]->getCode());
			isBattle=true;
			battle->startBattle(enemy[nowEnemy]->getCode());
			printf("???");
		}
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