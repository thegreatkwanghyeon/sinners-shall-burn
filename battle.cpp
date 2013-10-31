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

	sceneNum=normal;//기본 상태
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

	if(sceneNum == playerSkill){//플레이어가 스킬 시전중일떄
		playerSkillUpdate();
		return;
	}else if(sceneNum == enemySkill){
		enemySkillUpdate();
		return;
	}else if(sceneNum == checkSkill){//도트뎀 등을 판정.
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
		if(keyEvent == false && canUseSkill[i] != 0 && button[i]->checkMouseClick(event)){//클릭
			if(isBattle){
				useSkillNow=canUseSkill[i];
				useSkill(canUseSkill[i]);
				deltaClock.restart();
				keyEvent=true;

				//canUseSkill[i]=0;//노필요
				/*
				for(j=i+1;j<useCnt;j++){
					canUseSkill[j-1]=canUseSkill[j];
				}
				canUseSkill[useCnt-1]=0;*/
				useCnt--;
				srand(time(NULL));

				if(skill->data[useSkillNow].acc+(*player)->getAcc() < rand()%100){//0~99
					(*player)->setAcc(0);//추가 명중률을 다시 제거해준다.
					isMiss=true;
				}else{
					particle->setParticle(skill->data[useSkillNow].code);
				}
				skillTime.restart();
				//tp = skillEffect->getLocation();

				sceneNum=playerSkill;

				if(!isMiss){
					if(skill->data[useSkillNow].plusAcc > 0){
						(*player)->setAcc(skill->data[useSkillNow].plusAcc);//추가 명중률을 더해줌
					}
					if(skill->data[useSkillNow].guard > 0){
						(*player)->setGuard((*player)->getGuard()+skill->data[useSkillNow].guard);//추가 방어력을 더해줌
					}
					if(skill->data[useSkillNow].dot > 0){
						enemy->setDot(enemy->getDot()+skill->data[useSkillNow].dot);//도트뎀을 적에게 더해줌
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
//애니메이션 업데이트
	if(skillTime.getElapsedTime().asSeconds() >= skillEffectTime){//애니메이션 종료
		skillTime.restart();
		int damage=skill->data[useSkillNow].damage*puzzle->getPlusDamage();
		int pdamage=skill->data[useSkillNow].pdamage;

		//-------
		if(!isMiss){
			if(pdamage > 0){//내 체력 감소
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
			}else if(pdamage < 0){//내 체력 증가
				if(-1*pdamage > (*player)->getMaxHP()-(*player)->getHP()){
					hpGauge->setValue((*player)->getMaxHP()-(*player)->getHP());
					(*player)->setHP((*player)->getMaxHP());
				}else{
					hpGauge->setValue(-1*pdamage);
					(*player)->setHP((*player)->getHP()-pdamage);
				}
			}
			if(damage > 0){//적 체력 감소
				if(damage > enemy->getCurrentHp()){
					enemyGauge->setValue(-1*enemy->getCurrentHp());
					enemy->setCurrentHp(0);
				}else{
					enemyGauge->setValue(-1*damage);
					enemy->setCurrentHp(enemy->getCurrentHp()-damage);
				}
				//---
				puzzle->setPlusDamage(1.0);//보너스 데미지는 적에게 데미지를 줬을때만 무효화된다.
				//크리티컬은 적에게 일반 데미지를 줄떄만 발동된다.
			}else if(damage < 0){//적 체력 회복
				if(-1*damage > enemy->getMaxHp()-enemy->getCurrentHp()){
					enemyGauge->setValue(enemy->getMaxHp()-enemy->getCurrentHp());
					enemy->setCurrentHp(enemy->getMaxHp());
				}else{
					enemyGauge->setValue(-1*damage);
					enemy->setCurrentHp(enemy->getCurrentHp()-damage);
				}
			}
		}//미스가 났을 경우는 위 경우를 다 스킵함(아무 효과 없으니까)
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
			//몹의 서브스킬 판정
			if(rand()%100 <= enemy->getSubPro()){
				subSkill=true;
				particle->setParticle(enemy->getSubAni());
				(*player)->setDot((*player)->getDot()+skill->data[enemy->getSubAni()].dot);//플레이어에게 도트뎀
				//참고로 몬스터가 플레이어의 스킬을 배껴쓸떄는
				//도트뎀, 일반뎀 외의 효과(명중률 증감/데미지 흡수) 등을 사용 불가
				//도트뎀 프린트는 적/아군 바뀐거 적용하고 차후 하자 졸려 시발 으아
			}
		}
	}
	hpGauge->update();
	enemyGauge->update();
	return;
}
void Battle::enemySkillUpdate(){
//애니메이션 업데이트
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
	//아직 미설계
	//도트뎀 계산.
	//아직 플레이어가 도트뎀을 입는 경우, 적이 가드포함 스킬을 사용하는 경우, 적이 명중률 상승 효과를 보는 경우 등은 계산되지 않았다.
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
		hpGauge->setValue(hpGauge->getValue()*-1);//0으로 깔끔하게(가끔 처리 안되서)
		hpGauge->update();
		return 1;
	}
	if(enemy->getCurrentHp() <= 0){
		isBattle=false;
		enemyGauge->setValue(enemyGauge->getValue()*-1);//0으로 깔끔하게(가끔 처리 안되서)
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

		window.draw(enemy->getName());//몹 이름 출력!
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
		window.draw(text);//보너스뎀,명중률보정,가드,도트뎀 수치 저장하는 곳.
		window.draw(eText);//적의 평타 명중률과 도트데미지 기록
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
	if(isBattle == false || sceneNum == normal)//전투중이 아니거나, 전투중이어도 그냥 대기타고 있는경우.
		return true;
	return false;
}