#include "battle.h"
#include <string.h>

Battle::Battle(Player** _player){
	int i;

	player=_player;

	puzzle = new Puzzle();
	puzzle->setElement((*player)->useElement);

	enemy=new Enemy(1);

	tileset = new TileSet();
	faceTileset = new TileSet();

	texture.loadFromFile("img/skill2.png");
	texture = tileset->tileSet("img/skill2.png",30,30);

	face.loadFromFile("img/face.PNG");
	face = faceTileset->tileSet("img/face.PNG",150,200);

	sprite.setTexture(texture);
	sprite.setTextureRect(tileset->getTileSet(0));

	faceSprite.setTexture(face);
	faceSprite.setTextureRect(faceTileset->getTileSet(0));
	faceSprite.setPosition(325,455);

	skill = (*player)->skill;

	skillEffect=new Animation();

	skillEffect->addTile("img/skill01.PNG",250,250);
	skillEffect->setSpeed(0.5);
	skillEffect->setTileRange(sf::Vector2i(1,1),3);//디폴트.

	skillSprite.setPosition(515,215);

	font.loadFromFile("font/spike.ttf");
	text.setFont(font); 
	text.setString(L"bonus : 1.00");
	text.setPosition(450.0f, 250.0f);

	for(i=0;i<ViewSkill;i++){
		canUseSkill[i]=0;
		button[i] = new Button("img/skillButton.png");
		tooltip[i] = new Tooltip("img/tooltip.png");
		if(i < (ViewSkill/2)){
			button[i]->setPosition(830+(i*150),450);//dir-------------------------->
			tooltip[i]->setTooltip(L"", L"", sf::FloatRect(830+(i*150),450,100,100), 350);//dir-------------------------->
		}else{
			button[i]->setPosition(830+((i-(ViewSkill/2))*150),575);//dir-------------------------->
			tooltip[i]->setTooltip(L"", L"", sf::FloatRect(830+((i-(ViewSkill/2))*150),575,100,100), 350);//dir-------------------------->
		}
	}
	isBattle=false;

	hpGauge = new Gauge("img/hpgauge.png",100, 1, 1);
	hpGauge->setPosition(sf::Vector2i(0,0));

	enemyGauge = new Gauge("img/enemygauge.png",enemy->getMaxHp(),0,0);
	enemyGauge->setPosition(sf::Vector2i(357,150));

	sceneNum=normal;//기본 상태
}
void Battle::startBattle(int _code){
	delete(enemy);
	enemy = new Enemy(_code);
	isBattle=true;
	enemyGauge->setValue(enemy->getMaxHp());
	enemyGauge->setPosition(sf::Vector2i(357,150));
}

void Battle::update(sf::Event &event){
	int i,j,k,tp;
	int chk[200]={0,};

	float delta;
	
	for(i=0;i<ViewSkill;i++)
		canUseSkill[i]=0;
	for(i=0;i<200;i++){
		chk[i]=0;
	}

	puzzle->update(event);

	_snprintf(plusString, sizeof(plusString), "bonus : %.2f", puzzle->getPlusDamage());
	text.setString(plusString);

	if(sceneNum == playerSkill){//플레이어가 스킬 시전중일떄
		int damage=skill->data[useSkillNow].damage*puzzle->getPlusDamage();
		//애니메이션 업데이트
		skillEffect->update(&skillSprite, true);
		oldtemp=temp;
		temp = skillEffect->getLocation();
		if(temp < oldtemp){
			if(damage < 0){//회복.
				if(damage > (*player)->getMaxHP()-(*player)->getHP())
					hpGauge->setValue((*player)->getMaxHP()-(*player)->getHP());
				else
					hpGauge->setValue(-1*damage);
			}else{
				if(damage > enemy->getCurrentHp())
					enemyGauge->setValue(-1*enemy->getCurrentHp());
				else
					enemyGauge->setValue(-1*damage);
				//---
				enemy->setCurrentHp(enemy->getCurrentHp()-damage);
			}
			sceneNum=enemySkill;
			if(damage <= 0)//회복/도트계 스킬 사용시엔 보너스 수치 유지
				puzzle->setPlusDamage(1.0);
		}
		hpGauge->update();
		enemyGauge->update();
		return;
	}else if(sceneNum == enemySkill){
		//애니메이션 업데이트
		skillEffect->update(&skillSprite, true);
		oldtemp=temp;
		temp = skillEffect->getLocation();
		if(temp < oldtemp){
			(*player)->setHP((*player)->getHP()-enemy->getDamage());
			hpGauge->setValue(-1*enemy->getDamage());
			sceneNum=checkSkill;
		}
		hpGauge->update();
		enemyGauge->update();
		return;
	}else if(sceneNum == checkSkill){//도트뎀 등을 판정.
		sceneNum=normal;
	}

	if(keyEvent){
		delta=deltaClock.getElapsedTime().asSeconds();
		if(delta >= 0.5)
			keyEvent=false;
	}
	
	useCnt=0;
	for(i=puzzle->stackNum-1;i>=0;i--){
		for(j=0;j+i<puzzle->stackNum;j++){
			tp = makeCode(j,j+i);
			for(k=0;k<skill->skillNum;k++){
				if(tp == skill->data[k].needCode && useCnt < ViewSkill && chk[skill->data[k].code] == 0){
					//skill->data[k].use = true;
					chk[skill->data[k].code]=1;
					canUseSkill[useCnt++]=skill->data[k].code;
					break;
				}
			}
		}
	}
	for(i=0;i<useCnt;i++){
		button[i]->update(event);
		if(keyEvent == false && canUseSkill[i] != 0 && button[i]->checkMouseClick(event)){//클릭
			if(isBattle){
				useSkillNow=canUseSkill[i];
				useSkill(canUseSkill[i]);
				deltaClock.restart();
				keyEvent=true;

				canUseSkill[i]=0;
				useCnt--;

				skillEffect->setSpeed(0.5);
				skillEffect->setTileRange(sf::Vector2i(1,1),3);
				tp = skillEffect->getLocation();

				sceneNum=playerSkill;
			}else{
				(*player)->setHP((*player)->getHP()-1);
				hpGauge->setValue(-1);
				printf("전투중 아님\n");
			}
		}
		if(canUseSkill[i] != 0){
			if(i < (ViewSkill/2))
				tooltip[i]->setTooltip(skill->data[canUseSkill[i]].name, skill->data[canUseSkill[i]].effect, sf::FloatRect(830+(i*150),450,100,100), 350);//dir-------------------------->
			else
				tooltip[i]->setTooltip(skill->data[canUseSkill[i]].name, skill->data[canUseSkill[i]].effect, sf::FloatRect(830+((i-(ViewSkill/2))*150),575,100,100), 350);//dir-------------------------->
		}
		tooltip[i]->update();
	}

	hpGauge->update();
	enemyGauge->update();
}
bool Battle::getResult(){
	if(sceneNum != normal)
		return 0;
	if((*player)->getHP() <= 0){
		isBattle=false;
		return 1;
	}
	if(enemy->getCurrentHp() <= 0){
		isBattle=false;
		return 1;
	}
	return 0;
}

void Battle::draw(sf::RenderWindow &window){
	int i;
	if(sceneNum == playerSkill || sceneNum == enemySkill){
		window.draw(skillSprite);
		//return;
	}
	puzzle->draw(window);
	if(isBattle){
		window.draw(monster.name);
		enemyGauge->draw(window);
	}

	for(i=0;i<ViewSkill;i++){
		button[i]->draw(window);
	}
	for(i=0;i<ViewSkill;i++){
		if(i < (ViewSkill/2))
			sprite.setPosition(830+(i*150),450);//dir-------------------------->
		else
			sprite.setPosition(830+((i-(ViewSkill/2))*150),575);//dir-------------------------->
		sprite.setTextureRect(tileset->getTileSet(canUseSkill[i]));
		window.draw(sprite);
	}
	for(i=0;i<useCnt;i++){
		tooltip[i]->draw(window);
	}
	hpGauge->draw(window);
	window.draw(text);
	//---face---//
	faceSprite.setTextureRect(faceTileset->getTileSet((100-(*player)->getHP())/20));
	window.draw(faceSprite);
}
int Battle::makeCode(int s, int e){
	int i,re=1;

	if(e >= StackNum)
		return -1;
	for(i=s;i<=e;i++){
		re *= skill->check[puzzle->stack[i]->num];
	}
	return re;
}
void Battle::useSkill(int num){
	int i,j,k,l;
	int cnt=0;
	//printf("SKILL CODE : %d\nneed[0] : %d need[1] : %d\n\n",num,skill->data[num].need[0],skill->data[num].need[1]);
	for(i=0;i<ElementNum;i++){
		for(j=0;j<skill->data[num].need[i];j++){
			for(k=0;k<puzzle->stackNum;k++){
				if(puzzle->stack[k]->num == i){
					for(l=k;l<puzzle->stackNum-1;l++){
						puzzle->stack[l]->num=puzzle->stack[l+1]->num;
						puzzle->stack[l]->init_animation();
					}
					puzzle->stack[puzzle->stackNum-1]->num=-1;
					puzzle->stack[puzzle->stackNum-1]->init_animation();
					puzzle->stackNum--;
				}
			}
		}
	}
}