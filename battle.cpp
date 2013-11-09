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

	face.loadFromFile("img/portrait.png");
	face = faceTileset->tileSet("img/portrait.png",150,150);

	texture.loadFromFile("img/skills/empty.png");
	sprite.setTexture(texture);

	faceSprite.setTexture(face);
	faceSprite.setTextureRect(faceTileset->getTileSet(0));
	faceSprite.setPosition(325,455);

	skillBG.loadFromFile("img/skillBackground.png");
	skillBGSprite.setTexture(skillBG);
	skillBGSprite.setPosition(800,440);

	skill = (*player)->skill;

	particle = new ParticleList(640,200);
	particle->setParticle(1,"",false);

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
			button[i]->setPosition(836+(i*152),464);//dir-------------------------->
			tooltip[i]->setTooltip(L"", L"", sf::FloatRect(836+(i*152),464,80,80), 350);//dir-------------------------->
		}else{
			button[i]->setPosition(836+((i-(ViewSkill/2))*152),593);//dir-------------------------->
			tooltip[i]->setTooltip(L"", L"", sf::FloatRect(836+((i-(ViewSkill/2))*152),593,80,80), 350);//dir-------------------------->
		}
	}
	isBattle=false;

	hpGauge = new Gauge("img/hpgauge.png",100, 0, 1);
	hpGauge->setPosition(sf::Vector2i(0,0));

	enemyGauge = new Gauge("img/enemygauge.png",enemy->getMaxHp(),0,0);
	enemyGauge->setPosition(sf::Vector2i(357,150));

	timeGauge = new Gauge("img/hpgauge.png",puzzleLimit, 0, 1);
	timeGauge->setPosition(sf::Vector2i(300,300));

	sceneNum=normal;//기본 상태
	isMiss=false;
	subSkill=false;

	puzzleTime.restart();
}
Battle::~Battle(){
	delete puzzle;
	delete hpGauge;
	delete enemyGauge;
	delete timeGauge;
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

	if(isBattle)//비전투시에는 퍼즐의 업데이트를 제한한다
		puzzle->update(event);

	_snprintf(plusString, sizeof(plusString), "bonus : %.2f\ndot : %d\nguard : %d\nplusAcc : %d", puzzle->getPlusDamage(),(*player)->getDot(),(*player)->getGuard(),(*player)->getAcc());
	text.setString(plusString);//화면에 출력되는 나의 상태정보 텍스트

	_snprintf(plusString, sizeof(plusString), "dot : %d\nAcc : %d",enemy->getDot(),enemy->getAcc());
	eText.setString(plusString);//화면에 출력되는 적의 상태정보 텍스트

	if(sceneNum == playerSkill){//플레이어가 스킬 시전중일떄
		playerSkillUpdate();
		return;
	}else if(sceneNum == enemySkill){//적이 스킬/평타 시전중일때
		enemySkillUpdate();
		return;
	}else if(sceneNum == checkSkill){//도트뎀 등을 판정해주는 구역
		checkSkillUpdate();
		return;
	}
	
	for(i=0;i<ViewSkill;i++)//사용가능 스킬 스택 초기화하는 부분
		canUseSkill[i]=0;
	if(keyEvent){//중복클릭 방지
		delta=deltaClock.getElapsedTime().asSeconds();
		if(delta >= 0.5)
			keyEvent=false;
	}
	
	useCnt=0;//여기 아래부터는 스킬의 사용가능 검사해서 옆쪽 네모칸들 채우는거다
	for(i=puzzle->stackNum-1;i>=0;i--){
		for(j=0;j+i<puzzle->stackNum;j++){
			tp = makeCode(j,j+i);//
			for(k=0;k<skill->skillNum;k++){
				if(tp == skill->data[k].needCode && useCnt < ViewSkill && chk[skill->data[k].code] == 0){
					chk[skill->data[k].code]=1;
					canUseSkill[useCnt++]=skill->data[k].code;//canUseSkill에 사용가능 스킬 리스트를 고랭크 스킬부터 채움	
					//break;
				}
			}
		}
	}
	for(i=0;i<useCnt;i++){
		button[i]->update(event);
		if(keyEvent == false && canUseSkill[i] != 0 && button[i]->checkMouseClick(event)){//클릭
			if(isBattle){//여기가 스킬을 사용하였을떄의 상황

				useSkillNow=canUseSkill[i];//현재 사용한 스킬의 코드를 저장한다
				useSkill(canUseSkill[i]);//사용한 스킬에 맞게 스택 클리어

				deltaClock.restart();//연타방지
				keyEvent=true;//연타 방지

				useCnt--;//스킬 리스트 1개 감소...라는 의미긴 한데 위쪽에서 계속 정의되는 부분이니까 크게 신경쓸 필요는 없음
				srand(time(NULL));

				if(skill->data[useSkillNow].acc+(*player)->getAcc() < rand()%100){//미스판정(여기 구문은 미스가 난경우)
					isMiss=true;
					//particle->setParticle(skill->data[useSkillNow].code,skill->data[useSkillNow].soundLink,true);미스파티클
				}else{//적중
					particle->setParticle(skill->data[useSkillNow].code,skill->data[useSkillNow].soundLink,true);
				}
				(*player)->setAcc(0);//추가 명중률이 사용되었으므로 제거해줌
				//추가명중률 : 특정 기술 사용시 올라가는 것임. 양수일때는 내 다음 기술의 명중률을 그만큼 올려주고 음수일떄는 그만큼 적의 다음 공격 명중률을 깎아냄
				skillTime.restart();//스킬을 쓰고 나서 이펙트가 지속되는 시간을 측정하는 시간변수

				sceneNum=playerSkill;

				if(!isMiss){//미스가 나지 않았을 경우 도트/추가 방어력/추가 명중률을 판정함
					//추가 명중률
					if(skill->data[useSkillNow].plusAcc > 0)
						(*player)->setAcc(skill->data[useSkillNow].plusAcc);//추가 명중률을 더해줌
					else if(skill->data[useSkillNow].plusAcc < 0)
						enemy->setAcc(enemy->getAcc()+skill->data[useSkillNow].plusAcc);//명중률이 -값 : 적의 명중률을 그 값만큼 낮춘다는 것이다.
					//추가 방어력
					if(skill->data[useSkillNow].guard > 0)
						(*player)->setGuard((*player)->getGuard()+skill->data[useSkillNow].guard);//추가 방어력을 더해줌
					//도트뎀. 이건 적한테 적용되니까 적에게 추가해줌
					if(skill->data[useSkillNow].dot > 0)
						enemy->setDot(enemy->getDot()+skill->data[useSkillNow].dot);//도트뎀을 적에게 더해줌
					
				}
			}
		}
		if(canUseSkill[i] != 0){//이쪽은 툴팁 업데이트
			if(i < (ViewSkill/2))
				tooltip[i]->setTooltip(skill->data[canUseSkill[i]].name, skill->data[canUseSkill[i]].effect, sf::FloatRect(836+(i*152),464,80,80), 350);//dir-------------------------->
			else
				tooltip[i]->setTooltip(skill->data[canUseSkill[i]].name, skill->data[canUseSkill[i]].effect, sf::FloatRect(836+((i-(ViewSkill/2))*152),593,80,80), 350);//dir-------------------------->
		}
		tooltip[i]->update();
	}

	hpGauge->update();
	enemyGauge->update();

	if(isBattle){//이쪽은 제한시간 관련부분. 제한시간이 넘어가면 플레이어의 공격권은 상실되며 적이 바로 날 후려팬다. 현재 퍼즐 바로위 게이지가 바로 그것임.
		timeGauge->update();//이 게이지와 퍼즐타임 변수가 그 제한시간을 관리하는 물건.
		if(puzzleTime.getElapsedTime().asSeconds() >= 0.1){
			puzzleTime.restart();
			timeGauge->setValue(-1);
			if(timeGauge->getValue() <= 0){
				sceneNum=enemySkill;
				skillTime.restart();

				if(enemy->getAcc() >= rand()%100){//미스판정
					isMiss=false;
					if(rand()%100 <= enemy->getSubPro()){//서브스킬 발동시
						subSkill=true;
						particle->setParticle(enemy->getSubAni(),skill->data[enemy->getSubAni()].soundLink,true);
						(*player)->setDot((*player)->getDot()+skill->data[enemy->getSubAni()].dot);//플레이어에게 도트뎀
					}else{//걍 평타 떄릴시
						particle->setParticle(enemy->getAnimationNum(),enemy->getSoundLink(),true);//파티클 설정
					}
				}else{
					isMiss=true;
					//particle->setParticle(enemy->getAnimationNum(),enemy->getSoundLink(),true);미스파티클
				}
				enemy->setAcc(enemy->getMaxAcc());//플레이어가 스킬로 적의 명중률을 낮췄을경우 (현재 그 명중률보정이 적용됬으므로) 다시 원래대로 돌려줌
			}
		}
	}
}
void Battle::playerSkillUpdate(){
	if(skillTime.getElapsedTime().asSeconds() >= skillEffectTime){//파티클이 끝난 경우
		skillTime.restart();
		int damage=skill->data[useSkillNow].damage*puzzle->getPlusDamage();//적에게 주는 데미지
		int pdamage=skill->data[useSkillNow].pdamage;//내가 받을 데미지(내 스킬에 의한 데미지)

		//-------
		if(!isMiss){
			if(pdamage > 0){//내 체력 감소
				if(pdamage >= (*player)->getGuard()){//추가 방어력이 다 뚫릴 경우
					pdamage-=(*player)->getGuard();
					(*player)->setGuard(0);
				}else{//추가 방어력으로 상쇄가 되는경우
					(*player)->setGuard((*player)->getGuard()-pdamage);
					pdamage=0;
				}
				if(pdamage > (*player)->getHP()){//맞고 뒤지는 경우
					hpGauge->setValue(-1*(*player)->getHP());
					(*player)->setHP(0);
				}else{//맞아도 안죽는 경우
					hpGauge->setValue(-1*pdamage);
					(*player)->setHP((*player)->getHP()-pdamage);
				}
			}else if(pdamage < 0){//내 체력 증가
				if(-1*pdamage > (*player)->getMaxHP()-(*player)->getHP()){//체력회복으로 풀피나 그 이상이 되는경우
					hpGauge->setValue((*player)->getMaxHP()-(*player)->getHP());
					(*player)->setHP((*player)->getMaxHP());
				}else{//걍 회복
					hpGauge->setValue(-1*pdamage);
					(*player)->setHP((*player)->getHP()-pdamage);
				}
			}
			if(damage > 0){//적 체력 감소
				if(damage > enemy->getCurrentHp()){//적의 피통보다 데미지가 클 경우
					enemyGauge->setValue(-1*enemy->getCurrentHp());
					enemy->setCurrentHp(0);
				}else{//걍 데미지
					enemyGauge->setValue(-1*damage);
					enemy->setCurrentHp(enemy->getCurrentHp()-damage);
				}
				//---
				puzzle->setPlusDamage(1.0);//보너스 데미지는 적에게 데미지를 줬을때만 사용되도록 해놓음.
			}else if(damage < 0){//적 체력 회복(내 스킬의 효과로...)
				if(-1*damage > enemy->getMaxHp()-enemy->getCurrentHp()){//적이 풀피되는 경우
					enemyGauge->setValue(enemy->getMaxHp()-enemy->getCurrentHp());
					enemy->setCurrentHp(enemy->getMaxHp());
				}else{//걍 회복
					enemyGauge->setValue(-1*damage);
					enemy->setCurrentHp(enemy->getCurrentHp()-damage);
				}
			}
		}//미스가 났을 경우는 위 경우를 다 스킵함(아무 효과 없으니까)
		if((*player)->getHP() <= 0 || enemy->getCurrentHp() <= 0)//적이나 내가 사망
			sceneNum=checkSkill;
		else{//적의 턴으로 넘어감
			sceneNum=enemySkill;
			
			if(enemy->getAcc() >= rand()%100){//적의 공격이 적중이
				isMiss=false;
				if(rand()%100 <= enemy->getSubPro()){//적이 서브스킬 사용
					subSkill=true;
					particle->setParticle(enemy->getSubAni(),skill->data[enemy->getSubAni()].soundLink,true);//파티클 설정.
					(*player)->setDot((*player)->getDot()+skill->data[enemy->getSubAni()].dot);//플레이어에게 도트뎀. 현재 플레이어가 가진 도트수치에 적 스킬의 도트값을 더해준다.
					//참고로 몬스터가 플레이어의 스킬을 배껴쓸떄는
					//도트뎀, 일반뎀 외의 효과(명중률 증감/데미지 흡수) 등을 사용 불가
				}else{//적이 평타사용
					particle->setParticle(enemy->getAnimationNum(),enemy->getSoundLink(),true);
				}
			}else{
				isMiss=true;
				//particle->setParticle(enemy->getAnimationNum(),enemy->getSoundLink(),true);미스파티클
			}
			enemy->setAcc(enemy->getMaxAcc());//적에게 적용된 명중률 감소 등을 풀어준다.
		}
	}
	hpGauge->update();
	enemyGauge->update();
	return;
}
void Battle::enemySkillUpdate(){//적의 턴
	if(skillTime.getElapsedTime().asSeconds() >= skillEffectTime){//파티클이 끝난경우
		int damage;//적이 나에게 줄 데미지
		if(subSkill){//서브스킬 사용시엔 그 스킬의 데미지, 아니면 몬스터 고유의 평타딜
			damage = skill->data[enemy->getSubAni()].damage;
		}else{
			damage = enemy->getDamage();
		}
		
		if(!isMiss){//미스가 난 경우는 데미지 계산이 스킵된다.
			if(damage >= (*player)->getGuard()){//플레이어의 추가 방어력을 뚫었을경우
				damage-=(*player)->getGuard();
				(*player)->setGuard(0);
			}else{//추가방어를 뚫지 못하였을경우
				(*player)->setGuard((*player)->getGuard()-damage);
				damage=0;//데미지가 0이됨
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
	//도트뎀 계산.

	//여기가 도트뎀을 계산하는 곳임.
	//기존의 도트뎀 계산방식 : 일정 데미지가 추가되고 턴마가 그만큼 까임. 이 데미지는 턴마다 5씩 감소
	//개선할시에는 도트값을 지속되는 턴으로 하고 중첩시 턴을 길게 한다던가 하면 될거같다
	//하여튼 여기서 모든 도트딜을 계산하면 됨.

	if(enemy->getDot() > 0){//적이 가진 도트 계수를 바탕으로 딜링을 하고 5를 깎아줌. 
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
	if((*player)->getDot() > 0){//위와 같다.
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
	//턴이 끝난 후의 초기화파트
	isMiss=false;
	subSkill=false;
	sceneNum=normal;
	timeGauge->setValue(puzzleLimit-timeGauge->getValue());
	return;
}
bool Battle::getResult(){
	if(sceneNum != normal)
		return 0;
	if((*player)->getHP() <= 0){
		isBattle=false;
		puzzle->cleanStack();
		hpGauge->setValue(hpGauge->getValue()*-1);
		hpGauge->update();
		return 1;
	}
	if(enemy->getCurrentHp() <= 0){
		isBattle=false;
		puzzle->cleanStack();
		enemyGauge->setValue(enemyGauge->getValue()*-1);
		enemyGauge->update();
		return 1;
	}
	return 0;
}

void Battle::draw(sf::RenderWindow &window){
	int i;
	if(sceneNum == playerSkill || sceneNum == enemySkill){
		if(!isMiss){//차후 지울예정(미스에도 파티클 추가)
			particle->setLocationList();
		}
		//return;
	}
	particle->draw(window);
	
	if(isBattle){
		window.draw(skillBGSprite);
		puzzle->draw(window);
		timeGauge->draw(window);

		window.draw(enemy->getName());//몹 이름 출력!
		enemyGauge->draw(window);

		
		for(i=0;i<ViewSkill;i++){
			if(i < (ViewSkill/2))
				sprite.setPosition(836+(i*152),464);//dir-------------------------->
			else
				sprite.setPosition(836+((i-(ViewSkill/2))*152),593);//dir-------------------------->
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
Puzzle* Battle::getPuzzle(){
	return puzzle;
}