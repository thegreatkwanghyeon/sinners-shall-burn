#include "battle.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

Battle::Battle(Player** _player){
	int i;

	player=_player;

	puzzle = new Puzzle();
	puzzle->setElement((*player)->useElement);

	enemy=new Enemy(1);

	tileset = new TileSet();
	faceTileset = new TileSet();

	face.loadFromFile("img/face.PNG");
	face = faceTileset->tileSet("img/face.PNG",150,200);

	texture.loadFromFile("img/skills/empty.png");
	sprite.setTexture(texture);

	faceSprite.setTexture(face);
	faceSprite.setTextureRect(faceTileset->getTileSet(0));
	faceSprite.setPosition(325,455);

	skillBG.loadFromFile("img/skillBackground.png");
	skillBGSprite.setTexture(skillBG);
	skillBGSprite.setPosition(800,440);

	skill = (*player)->skill;

	particle = new ParticleList(0,0);
	particle->setParticle(1);

	font.loadFromFile("font/spike.ttf");
	text.setFont(font); 
	text.setString(L"bonus : 1.00\ndot : 0\nguard : 0\nplusAcc : 0");
	text.setPosition(0.0f, 110.0f);


	eText.setFont(font); 
	eText.setString(L"dot : 0\nAcc : 0");
	eText.setPosition(1000.0f, 200.0f);

	for(i=0;i<ViewSkill;i++){
		canUseSkill[i]=0;
		button[i] = new Button("img/skills/skillcover.png");
		button[i]->setClickSound("sounds/button/click.wav");
		button[i]->setHoverSound("sounds/button/hover.wav");
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

	sceneNum=normal;//�⺻ ����
	isMiss=false;
	subSkill=false;

}
Battle::~Battle(){
	delete puzzle;
	delete hpGauge;
	delete enemyGauge;
	for(int i=0;i<ViewSkill;i++){
		delete button[i];
		delete tooltip[i];
	}
	
	delete enemy;
	//delete player;
	delete tileset;
	delete faceTileset;
}
void Battle::startBattle(int _code){
	delete(enemy);
	enemy = new Enemy(_code);
	isBattle=true;
	delete(enemyGauge);
	enemyGauge = new Gauge("img/enemygauge.png",enemy->getMaxHp(),0,0);
	enemyGauge->setPosition(sf::Vector2i(357,150));

	(*player)->setAcc(0);
	(*player)->setGuard(0);
	(*player)->setDot(0);
}

void Battle::update(sf::Event &event){
	int i,j,k,tp;
	int chk[200]={0,};

	float delta;

	for(i=0;i<200;i++){
		chk[i]=0;
	}
	particle->update();

	if(isBattle)
		puzzle->update(event);

	_snprintf(plusString, sizeof(plusString), "bonus : %.2f\ndot : %d\nguard : %d\nplusAcc : %d", puzzle->getPlusDamage(),(*player)->getDot(),(*player)->getGuard(),(*player)->getAcc());
	text.setString(plusString);

	_snprintf(plusString, sizeof(plusString), "dot : 0\nAcc : 0",enemy->getDot(),enemy->getAcc());
	eText.setString(plusString);

	if(sceneNum == playerSkill){//�÷��̾ ��ų �������ϋ�
		playerSkillUpdate();
		return;
	}else if(sceneNum == enemySkill){
		enemySkillUpdate();
		return;
	}else if(sceneNum == checkSkill){//��Ʈ�� ���� ����.
		checkSkillUpdate();
		return;
	}
	
	for(i=0;i<ViewSkill;i++)
		canUseSkill[i]=0;
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
		if(keyEvent == false && canUseSkill[i] != 0 && button[i]->checkMouseClick(event)){//Ŭ��
			if(isBattle){
				useSkillNow=canUseSkill[i];
				useSkill(canUseSkill[i]);
				deltaClock.restart();
				keyEvent=true;

				//canUseSkill[i]=0;//���ʿ�
				/*
				for(j=i+1;j<useCnt;j++){
					canUseSkill[j-1]=canUseSkill[j];
				}
				canUseSkill[useCnt-1]=0;*/
				useCnt--;
				srand(time(NULL));

				if(skill->data[useSkillNow].acc+(*player)->getAcc() < rand()%100){//0~99
					(*player)->setAcc(0);//�߰� ���߷��� �ٽ� �������ش�.
					isMiss=true;
				}else{
					particle->setParticle(skill->data[useSkillNow].code);
				}
				skillTime.restart();
				//tp = skillEffect->getLocation();

				sceneNum=playerSkill;

				if(!isMiss){
					if(skill->data[useSkillNow].plusAcc > 0){
						(*player)->setAcc(skill->data[useSkillNow].plusAcc);//�߰� ���߷��� ������
					}
					if(skill->data[useSkillNow].guard > 0){
						(*player)->setGuard((*player)->getGuard()+skill->data[useSkillNow].guard);//�߰� ������ ������
					}
					if(skill->data[useSkillNow].dot > 0){
						enemy->setDot(enemy->getDot()+skill->data[useSkillNow].dot);//��Ʈ���� ������ ������
					}
				}
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
void Battle::playerSkillUpdate(){
//�ִϸ��̼� ������Ʈ
	if(skillTime.getElapsedTime().asSeconds() >= skillEffectTime){//�ִϸ��̼� ����
		skillTime.restart();
		int damage=skill->data[useSkillNow].damage*puzzle->getPlusDamage();
		int pdamage=skill->data[useSkillNow].pdamage;

		//-------
		if(!isMiss){
			if(pdamage > 0){//�� ü�� ����
				if(pdamage >= (*player)->getGuard()){
					pdamage-=(*player)->getGuard();
					(*player)->setGuard(0);
				}else{
					(*player)->setGuard((*player)->getGuard()-pdamage);
					pdamage=0;
				}
				if(pdamage > (*player)->getHP()){
					hpGauge->setValue(-1*(*player)->getHP());
					(*player)->setHP(0);
				}else{
					hpGauge->setValue(-1*pdamage);
					(*player)->setHP((*player)->getHP()-pdamage);
				}
			}else if(pdamage < 0){//�� ü�� ����
				if(-1*pdamage > (*player)->getMaxHP()-(*player)->getHP()){
					hpGauge->setValue((*player)->getMaxHP()-(*player)->getHP());
					(*player)->setHP((*player)->getMaxHP());
				}else{
					hpGauge->setValue(-1*pdamage);
					(*player)->setHP((*player)->getHP()-pdamage);
				}
			}
			if(damage > 0){//�� ü�� ����
				if(damage > enemy->getCurrentHp()){
					enemyGauge->setValue(-1*enemy->getCurrentHp());
					enemy->setCurrentHp(0);
				}else{
					enemyGauge->setValue(-1*damage);
					enemy->setCurrentHp(enemy->getCurrentHp()-damage);
				}
				//---
				puzzle->setPlusDamage(1.0);//���ʽ� �������� ������ �������� �������� ��ȿȭ�ȴ�.
				//ũ��Ƽ���� ������ �Ϲ� �������� �ً��� �ߵ��ȴ�.
			}else if(damage < 0){//�� ü�� ȸ��
				if(-1*damage > enemy->getMaxHp()-enemy->getCurrentHp()){
					enemyGauge->setValue(enemy->getMaxHp()-enemy->getCurrentHp());
					enemy->setCurrentHp(enemy->getMaxHp());
				}else{
					enemyGauge->setValue(-1*damage);
					enemy->setCurrentHp(enemy->getCurrentHp()-damage);
				}
			}
		}//�̽��� ���� ���� �� ��츦 �� ��ŵ��(�ƹ� ȿ�� �����ϱ�)
		if((*player)->getHP() <= 0 || enemy->getCurrentHp() <= 0)
			sceneNum=checkSkill;
		else{
			sceneNum=enemySkill;
			particle->setParticle(enemy->getAnimationNum());
			if(enemy->getAcc() >= rand()%100){
				isMiss=false;
			}else{
				isMiss=true;
			}
			//���� ���꽺ų ����
			if(rand()%100 <= enemy->getSubPro()){
				subSkill=true;
				particle->setParticle(enemy->getSubAni());
				(*player)->setDot((*player)->getDot()+skill->data[enemy->getSubAni()].dot);//�÷��̾�� ��Ʈ��
				//����� ���Ͱ� �÷��̾��� ��ų�� �貸������
				//��Ʈ��, �Ϲݵ� ���� ȿ��(���߷� ����/������ ���) ���� ��� �Ұ�
				//��Ʈ�� ����Ʈ�� ��/�Ʊ� �ٲ�� �����ϰ� ���� ���� ���� �ù� ����
			}
		}
	}
	hpGauge->update();
	enemyGauge->update();
	return;
}
void Battle::enemySkillUpdate(){
//�ִϸ��̼� ������Ʈ
	if(skillTime.getElapsedTime().asSeconds() >= skillEffectTime){
		int damage;
		if(subSkill){
			damage = skill->data[enemy->getSubAni()].damage;
		}else{
			damage = enemy->getDamage();
		}
		
		if(!isMiss){
			if(damage >= (*player)->getGuard()){
				damage-=(*player)->getGuard();
				(*player)->setGuard(0);
			}else{
				(*player)->setGuard((*player)->getGuard()-damage);
				damage=0;
			}
			(*player)->setHP((*player)->getHP()-damage);
			hpGauge->setValue(-1*damage);
		}
		skillTime.restart();
		sceneNum=checkSkill;
	}
	hpGauge->update();
	enemyGauge->update();
}
void Battle::checkSkillUpdate(){
	//���� �̼���
	//��Ʈ�� ���.
	//���� �÷��̾ ��Ʈ���� �Դ� ���, ���� �������� ��ų�� ����ϴ� ���, ���� ���߷� ��� ȿ���� ���� ��� ���� ������ �ʾҴ�.
	if(enemy->getDot() > 0){
		if(enemy->getDot() > enemy->getCurrentHp()){
			enemyGauge->setValue(-1*enemy->getCurrentHp());
			enemy->setCurrentHp(0);
		}else{
			enemyGauge->setValue(-1*enemy->getDot());
			enemy->setCurrentHp(enemy->getCurrentHp()-enemy->getDot());
		}
		if(enemy->getDot() > 5)
			enemy->setDot(enemy->getDot()-5);
		else
			enemy->setDot(0);
	}
	if((*player)->getDot() > 0){
		if((*player)->getDot() > (*player)->getHP()){
			hpGauge->setValue(-1*(*player)->getHP());
			(*player)->setHP(0);
		}else{
			hpGauge->setValue(-1*(*player)->getDot());
			(*player)->setHP((*player)->getHP()-(*player)->getDot());
		}
		if((*player)->getDot() > 5)
			(*player)->setDot((*player)->getDot()-5);
		else
			(*player)->setDot(0);
	}
	isMiss=false;
	subSkill=false;
	sceneNum=normal;
	return;
}
bool Battle::getResult(){
	if(sceneNum != normal)
		return 0;
	if((*player)->getHP() <= 0){
		isBattle=false;
		hpGauge->setValue(hpGauge->getValue()*-1);//0���� ����ϰ�(���� ó�� �ȵǼ�)
		hpGauge->update();
		return 1;
	}
	if(enemy->getCurrentHp() <= 0){
		isBattle=false;
		enemyGauge->setValue(enemyGauge->getValue()*-1);//0���� ����ϰ�(���� ó�� �ȵǼ�)
		enemyGauge->update();
		return 1;
	}
	return 0;
}

void Battle::draw(sf::RenderWindow &window){
	int i;
	if(sceneNum == playerSkill || sceneNum == enemySkill){
		if(!isMiss){
			particle->setLocationList();
		}
		//return;
	}
	particle->draw(window);
	
	if(isBattle){
		window.draw(skillBGSprite);
		puzzle->draw(window);

		window.draw(enemy->getName());//�� �̸� ���!
		enemyGauge->draw(window);

		
		for(i=0;i<ViewSkill;i++){
			if(i < (ViewSkill/2))
				sprite.setPosition(830+(i*150),450);//dir-------------------------->
			else
				sprite.setPosition(830+((i-(ViewSkill/2))*150),575);//dir-------------------------->
			//sprite.setTextureRect(tileset->getTileSet(canUseSkill[i]));
			if(canUseSkill[i] != 0){
				texture.loadFromFile(skill->data[canUseSkill[i]].link);
			}else{
				texture.loadFromFile("img/skills/empty.png");
			}
			window.draw(sprite);
		}
		for(i=0;i<ViewSkill;i++){
			button[i]->draw(window);
		}
		for(i=0;i<useCnt;i++){
			tooltip[i]->draw(window);
		}
		window.draw(text);//���ʽ���,���߷�����,����,��Ʈ�� ��ġ �����ϴ� ��.
		window.draw(eText);//���� ��Ÿ ���߷��� ��Ʈ������ ���
	}
		
	hpGauge->draw(window);
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
bool Battle::getState(){
	if(isBattle == false || sceneNum == normal)//�������� �ƴϰų�, �������̾ �׳� ���Ÿ�� �ִ°��.
		return true;
	return false;
}