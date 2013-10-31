#include "gamescene.h"
#include "stdio.h"

GameScene::GameScene(){
	rayCastingScene = new RayCastingScene();

	floorNum=0;
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
	/*
	for(int i=0;i<3;i++){
		enemy.push_back(new Enemy(1));
	}

	pEnemy = &enemy; 

	texture.loadFromFile("img/enemies/ghoul.png");

	enemy[0]->setPosition(sf::Vector2f(3.5, 3.5));
	enemy[0]->setTexture(texture);

	enemy[1]->setPosition(sf::Vector2f(4.5, 3.5));
	enemy[1]->setTexture(texture);

	enemy[2]->setPosition(sf::Vector2f(3.5, 4.5));
	enemy[2]->setTexture(texture);

	rayCastingScene->setEnemies(pEnemy); //����ĳ���� ������ �Ѱ���
	*/
	makeEnemys();

	isBattle=false;
	isOver=false;
	nowEnemy=0;

	font.loadFromFile("font/spike.ttf");
	text.setFont(font); 
	text.setString(L"GAME OVER");
	text.setPosition(450.0f, 100.0f);

	overButton = new Button("img/button.png");
	overButton->setClickSound("sounds/button/click.wav");
	overButton->setHoverSound("sounds/button/hover.wav");
	overButton->setPosition(500,500);
	overButton->setText("Return",18);

	changeFlag=false;
	printf("now : %d(floor)\nportal : %d %d\n",floorNum,portal.x,portal.y);

	pause = new Pause();
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
	if(pause->getState()){//�����Ǿ����� true ����
		pause->update(event);
		return;
	}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && battle ->getState() && !isOver){//ESC�� ������ ��Ʋ���� Ư���� ��Ȳ(����ĳ������ ���� ����)�� ���°��. ���ӿ����� �ߴ°� �� �׷���?
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
			isBattle=true;
			battle->startBattle(enemy[nowEnemy]->getCode());
		}
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
		window.draw(text);
		overButton->draw(window);
	}
	//-------------�ϴ� �� ����� ����------------
	if(pause->getState()){//�Ͻ�������
		pause->draw(window);
	}
}
int GameScene::changeScene(){
	if(pause->isEnd())//����
		return 0;
	if(changeFlag || pause->isGoTitle())
		return 1;
	else if(floorNum >= 1){
		return 3;
	}
	return -1;
}
void GameScene::makeEnemys(){
	sf::Vector2i tp;
	for(int i=0;i<enemy.size();i++)
		enemy.pop_back();
	for(int i=0;i<5;i++){
		enemy.push_back(new Enemy(1));
		texture.loadFromFile("img/enemies/ghoul.png");

		tp=makemap->getEnemyPos(i,5);
		enemy[i]->setPosition(translatePosition((double)tp.x+0.5,(double)tp.y+0.5));
		enemy[i]->setPosition(sf::Vector2f(enemy[i]->getPosition().x+1,enemy[i]->getPosition().y));
		//printf("%d : %.2f %.2f ---\n",i,enemy[i]->getPosition().x,enemy[i]->getPosition().y);
		enemy[i]->setTexture(texture);
	}

	pEnemy = &enemy; 

	rayCastingScene->setEnemies(pEnemy); //����ĳ���� ������ �Ѱ���
}
sf::Vector2f GameScene::translatePosition(float _x, float _y){
	return sf::Vector2f(MapX-_x-1,_y);
}