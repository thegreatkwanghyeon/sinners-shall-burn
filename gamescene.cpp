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
			alpha-=5;//--는 너무 느림;;
			if(alpha < 255)
				rec.setFillColor(sf::Color::Color(0,0,0,alpha));
		}
		return;
	}
	if(pause->getState()){//정지되었으면 true 리턴
		pause->update(event);
		return;
	}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && battle ->getState() && !isOver && !rayCastingScene->isMove()){//ESC를 눌렀고 배틀에서 특별한 상황(레이캐스팅의 무빙 포함)이 없는경우. 게임오버떄 뜨는건 좀 그렇지?
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
	if(isBattle){//전투
		tooltip->update();
		if(battle->getResult() != 0){//전투중일 때, 전투가 끝났는지를 판정하는 함수이다.
			isBattle=false;
			if(player->getHP() <= 0){
				isOver=true;
				rayCastingScene->setShader((std::string)"blood");
			}else
				enemy.erase(enemy.begin()+nowEnemy);//전투 끝나면 적 삭제. 단 내가 안죽었을때.
		}
	}else{//비전투
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
	//---맵체인지 테스트---//
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
	//-------------일단 다 출력은 해줌------------
	if(pause->getState()){//일시정지시
		pause->draw(window);
	}
	window.draw(rec);
	if(rec.getFillColor().a > 0){//특이한 경우 : 층 이동!
		window.draw(sprite);
		window.draw(fText);
	}
}
int GameScene::changeScene(){
	if(pause->isEnd())//종료
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
			enemy.push_back(new Enemy(floorNum+3));//+3짜리 튀어나오게;..
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

	rayCastingScene->setEnemies(pEnemy); //레이캐스팅 씬으로 넘겨줌
	//전환효과도 여기에 추가하도록 한다	
	rec.setFillColor(sf::Color::Color(0,0,0,255));//검정, 알파값 255
	alpha=ChangeTime;
	alphaTime.restart();

	_snprintf(plusString, sizeof(plusString), "F%d",floorNum);
	fText.setString(plusString);
}
sf::Vector2f GameScene::translatePosition(float _x, float _y){
	return sf::Vector2f(MapX-_x-1,_y);
}