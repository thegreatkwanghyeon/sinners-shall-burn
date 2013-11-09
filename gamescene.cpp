#include "gamescene.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GameScene::GameScene(){
	rayCastingScene = new RayCastingScene();

	rec.setSize(sf::Vector2f(1280,720));
	rec.setPosition(0,0);

	floorNum=1;
	makemap = new MakeMap();
	makemap->buildMap(floorNum);
	for(int i=0;i<MapY;i++){
		for(int j=0;j<MapX;j++){
			worldMap[i][j]=makemap->getMap(i,j);
		}
	}
	rayCastingScene->setMap(worldMap);
	rayCastingScene->setPos(translatePosition(1.5,2.5));
	portal=makemap->getPortal();
	rayCastingScene->setPortal(portal);
	player = new Player();
	pPlayer=&player;
	battle = new Battle(pPlayer);

	makeEnemys();

	isBattle=false;
	isOver=false;
	nowEnemy=0;

	font.loadFromFile("font/spike.ttf");
	text.setFont(font);
	text.setString(L"GAME OVER");
	text.setPosition(480.0f, 175.0f);
	text.setCharacterSize(50);

	fText.setFont(font);
	fText.setPosition(600.0f, 160.0f);
	fText.setCharacterSize(80);

	overButton = new Button("img/startbutton.png");
	overButton->setClickSound("sounds/button/click.wav");
	overButton->setHoverSound("sounds/button/hover.wav");
	overButton->setPosition(510,500);
	overButton->setText("Return",18);

	changeFlag=false;

	pause = new Pause();
	tooltip = new Tooltip("img/tooltip.png");
	tooltip->setTooltip(L"", L"", sf::FloatRect(500,0,280,415), 350);

	titleTexture.loadFromFile("img/title.png");
	sprite.setTexture(titleTexture);
	sprite.setPosition(390,150);
}
GameScene::~GameScene(){
	delete battle;
	delete rayCastingScene;
	delete pause;
	delete player;
	delete overButton;
	delete makemap;
}
void GameScene::update(sf::Event &event){
	if(rec.getFillColor().a != 0){
		if(alphaTime.getElapsedTime().asSeconds() >= 0.01){
			alphaTime.restart();
			alpha-=5;//--�� �ʹ� ����;;
			if(alpha < 255)
				rec.setFillColor(sf::Color::Color(0,0,0,alpha));
		}
		return;
	}
	if(pause->getState()){//�����Ǿ����� true ����
		pause->update(event);
		return;
	}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && battle ->getState() && !isOver && !rayCastingScene->isMove()){//ESC�� ������ ��Ʋ���� Ư���� ��Ȳ(����ĳ������ ���� ����)�� ���°��. ���ӿ����� �ߴ°� �� �׷���?
		pause->pauseOn();
		return;
	}
	if(isOver){
		//rayCastingScene->setShader((std::string)"blood");
		overButton->update(event);
		if(overButton->checkMouseClick(event)){
			changeFlag=true;
		}
		return;
	}
	battle->update(event);
	if(isBattle){//����
		tooltip->update();
		if(battle->getResult() != 0){//�������� ��, ������ ���������� �����ϴ� �Լ��̴�.
			isBattle=false;
			if(player->getHP() <= 0){
				isOver=true;
				rayCastingScene->setShader((std::string)"blood");
			}else
				enemy.erase(enemy.begin()+nowEnemy);//���� ������ �� ����. �� ���� ���׾�����.
		}
	}else{//������
		rayCastingScene->update(event);
		
		nowEnemy=rayCastingScene->isBattle();
		if(nowEnemy != -1){
			tooltip->setTooltip(enemy[nowEnemy]->getName().getString(),enemy[nowEnemy]->getIntro(),sf::FloatRect(500,0,280,415), 350);
			isBattle=true;
			battle->startBattle(enemy[nowEnemy]->getCode());
		}
	}
	if(rayCastingScene->isGetReNum()){
		battle->getPuzzle()->setReNum(battle->getPuzzle()->getReNum()+1);
	}
	//---��ü���� �׽�Ʈ---//
	if(rayCastingScene->isMapChange()){
		makemap->buildMap(++floorNum);
		for(int i=0;i<MapY;i++){
			for(int j=0;j<MapX;j++){
				worldMap[i][j]=makemap->getMap(i,j);
			}
		}
		portal=makemap->getPortal();
		rayCastingScene->setPortal(portal);
		rayCastingScene->setMap(worldMap);
		rayCastingScene->setPos(translatePosition(1.5,2.5));
		makeEnemys();
		printf("now : %d(floor)\nportal : %d %d\n",floorNum,portal.x,portal.y);
	}
}

void GameScene::draw(sf::RenderWindow &window){
	//---
	rayCastingScene->draw(window);
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 1280, 700));

	view.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
	window.setView(view);
	battle->draw(window);
	if(isOver){
		window.draw(sprite);
		window.draw(text);
		overButton->draw(window);
	}
	if(isBattle && !isOver && !pause->getState())
		tooltip->draw(window);
	//-------------�ϴ� �� ����� ����------------
	if(pause->getState()){//�Ͻ�������
		pause->draw(window);
	}
	window.draw(rec);
	if(rec.getFillColor().a > 0){//Ư���� ��� : �� �̵�!
		window.draw(sprite);
		window.draw(fText);
	}
}
int GameScene::changeScene(){
	if(pause->isEnd())//����
		return 0;
	if(changeFlag || pause->isGoTitle())
		return 1;
	else if(floorNum > EndStage){
		return 3;
	}
	return -1;
}
void GameScene::makeEnemys(){
	sf::Vector2i tp;
	while(1){
		enemy.pop_back();
		if(enemy.size() <= 0)
			break;
	}
	srand(time(NULL));
	for(int i=0;i<=EnemyNum;i++){
		if(i == EnemyNum)
			enemy.push_back(new Enemy(floorNum+3));//+3¥�� Ƣ�����;..
		else
			enemy.push_back(new Enemy(rand()%3+(floorNum)));
		texture.loadFromFile(enemy[i]->getTextureName());

		tp=makemap->getEnemyPos(i,EnemyNum);
		enemy[i]->setPosition(translatePosition((double)tp.x+0.5,(double)tp.y+0.5));
		enemy[i]->setPosition(sf::Vector2f(enemy[i]->getPosition().x+1,enemy[i]->getPosition().y));
		printf("%d : %.2f %.2f [%d]<%d %d>---\n",i,enemy[i]->getPosition().x,enemy[i]->getPosition().y,enemy[i]->getCode(),i,enemy.size());
		enemy[i]->setTexture(texture);
	}

	pEnemy = &enemy; 

	rayCastingScene->setEnemies(pEnemy); //����ĳ���� ������ �Ѱ���
	//��ȯȿ���� ���⿡ �߰��ϵ��� �Ѵ�	
	rec.setFillColor(sf::Color::Color(0,0,0,255));//����, ���İ� 255
	alpha=ChangeTime;
	alphaTime.restart();

	_snprintf(plusString, sizeof(plusString), "F%d",floorNum);
	fText.setString(plusString);
}
sf::Vector2f GameScene::translatePosition(float _x, float _y){
	return sf::Vector2f(MapX-_x-1,_y);
}