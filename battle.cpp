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
	statusTileset = new TileSet();

	face.loadFromFile("img/portrait.png");
	face = faceTileset->tileSet("img/portrait.png",150,150);

	statusTexture.loadFromFile("img/statuseffect.png");
	statusTexture = statusTileset->tileSet("img/statuseffect.png",25,25);
	
	status.setTexture(statusTexture);
	//status.setTextureRect(statusTileset->getTileSet(0));

	texture.loadFromFile("img/skills/empty.png");
	sprite.setTexture(texture);

	faceSprite.setTexture(face);
	faceSprite.setTextureRect(faceTileset->getTileSet(0));
	faceSprite.setPosition(0,515);

	skillBG.loadFromFile("img/skillBackground.png");
	skillBGSprite.setTexture(skillBG);
	skillBGSprite.setPosition(800,440);

	skill = (*player)->skill;

	particle = new ParticleList(640,200);

	font.loadFromFile("font/aPinoL.ttf");
	text.setFont(font); 
	text.setCharacterSize(20);
	text.setString(L"�߰� ���ݷ� : 1.00\n�߰� ���� : 0\n�߰� ���߷� : 0");
	text.setPosition(150.0f, 550.0f);


	eText.setFont(font); 
	eText.setString(L"���߷� : 0 ü�� : 100/100");
	eText.setPosition(640.0f, 80.0f);
	eText.setOrigin(eText.getLocalBounds().width/2,0);
	eText.setCharacterSize(20);

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
	hpGauge->setPosition(sf::Vector2i(5,665));
	hpGauge->setTextElement(20,sf::Color::White);

	enemyGauge = new Gauge("img/enemygauge.png",enemy->getMaxHp(),0,-1);
	enemyGauge->setPosition(sf::Vector2i(440,20));

	timeGauge = new Gauge("img/puzzleTimeGauge.png",puzzleLimit, 0, -1);
	timeGauge->setPosition(sf::Vector2i(PStartX+320,PStartY-5));

	sceneNum=normal;//�⺻ ����
	isMiss=false;
	subSkill=false;

	puzzleTime.restart();

	for(i=0;i<8;i++){
		eStatusTip[i] = new Tooltip("img/tooltip.png");
		pStatusTip[i] = new Tooltip("img/tooltip.png");
		
		eStatusTip[i]->setTooltip(L"", L"", sf::FloatRect(460+(i*30),80,25,25),350);
		pStatusTip[i]->setTooltip(L"", L"", sf::FloatRect(160+(i*30),630,25,25),350);
	}
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
	//delete (*player);
	delete tileset;
	delete faceTileset;
	delete statusTileset;

	for(int i=0;i<8;i++){
		delete pStatusTip[i];
		delete eStatusTip[i];
	}

	delete particle;
	///delete skill;
}
void Battle::startBattle(int _code){
	delete(enemy);
	enemy = new Enemy(_code);
	isBattle=true;
	delete(enemyGauge);
	enemyGauge = new Gauge("img/enemygauge.png",enemy->getMaxHp(),0,-1);
	enemyGauge->setPosition(sf::Vector2i(440,20));

	(*player)->setAcc(0);
	(*player)->setGuard(0);
}

void Battle::update(sf::Event &event){
	int i, j, k, tp;
	int chk[200] = { 0, };

	float delta;

	for (i = 0; i < 200; i++){
		chk[i] = 0;
	}
	for(i=0;i<8;i++){
		pStatusTip[i]->update();
		eStatusTip[i]->update();
	}
	particle->update();
	

	if(isBattle)//�������ÿ��� ������ ������Ʈ�� �����Ѵ�
		puzzle->update(event);

	_swprintf(plusString, L"�߰� ������ : %.2f\n�߰� ���� : %d\n�߰� ���߷� : %d", puzzle->getPlusDamage(),(*player)->getGuard(),(*player)->getAcc());
	text.setString(plusString);//ȭ�鿡 ��µǴ� ���� �������� �ؽ�Ʈ

	_swprintf(plusString, L" ���߷� : %d ü�� %d/%d",enemy->getAcc(),enemy->getCurrentHp(),enemy->getMaxHp());
	eText.setOrigin(eText.getLocalBounds().width/2,0);
	eText.setString(plusString);//ȭ�鿡 ��µǴ� ���� �������� �ؽ�Ʈ

	if(sceneNum == playerSkill){//�÷��̾ ��ų �������ϋ�
		playerSkillUpdate();
		return;
	}else if(sceneNum == enemySkill){//���� ��ų/��Ÿ �������϶�
		enemySkillUpdate();
		return;
	}else if(sceneNum == checkSkill){//��Ʈ�� ���� �������ִ� ����
		checkSkillUpdate();
		return;
	}
	
	for(i=0;i<ViewSkill;i++)//��밡�� ��ų ���� �ʱ�ȭ�ϴ� �κ�
		canUseSkill[i]=0;
	if(keyEvent){//�ߺ�Ŭ�� ����
		delta=deltaClock.getElapsedTime().asSeconds();
		if(delta >= 0.5)
			keyEvent=false;
	}
	
	useCnt=0;//���� �Ʒ����ʹ� ��ų�� ��밡�� �˻��ؼ� ���� �׸�ĭ�� ä��°Ŵ�
	for(i=puzzle->stackNum-1;i>=0;i--){
		for(j=0;j+i<puzzle->stackNum;j++){
			tp = makeCode(j,j+i);//
			for(k=0;k<skill->skillNum;k++){
				if(tp == skill->data[k].needCode && useCnt < ViewSkill && chk[skill->data[k].code] == 0){
					chk[skill->data[k].code]=1;
					canUseSkill[useCnt++]=skill->data[k].code;//canUseSkill�� ��밡�� ��ų ����Ʈ�� ��ũ ��ų���� ä��	
					//break;
				}
			}
		}
	}
	if(cheatSkill){//��ųġƮ
		canUseSkill[0]=cheatSkillNum;
		if(useCnt == 0)
			useCnt++;
	}
	for(i=0;i<useCnt;i++){
		button[i]->update(event);
		if(keyEvent == false && canUseSkill[i] != 0 && button[i]->checkMouseClick(event)){//Ŭ��
			if(isBattle){//���Ⱑ ��ų�� ����Ͽ������� ��Ȳ

				useSkillNow=canUseSkill[i];//���� ����� ��ų�� �ڵ带 �����Ѵ�
				if(!cheatSkill || i != 0)
					useSkill(canUseSkill[i]);//����� ��ų�� �°� ���� Ŭ����

				deltaClock.restart();//��Ÿ����
				keyEvent=true;//��Ÿ ����

				useCnt--;//��ų ����Ʈ 1�� ����...��� �ṉ̀� �ѵ� ���ʿ��� ��� ���ǵǴ� �κ��̴ϱ� ũ�� �Ű澵 �ʿ�� ����
				srand(time(NULL));

				if(skill->data[useSkillNow].acc+(*player)->getAcc() < rand()%100){//�̽�����(���� ������ �̽��� �����)
					isMiss=true;
					particle->setParticle(100,"sounds/skill/miss.ogg",true);
				}else{//����
					particle->setParticle(skill->data[useSkillNow].code,skill->data[useSkillNow].soundLink,true);
				}
				(*player)->setAcc(0);//�߰� ���߷��� ���Ǿ����Ƿ� ��������
				//�߰����߷� : Ư�� ��� ���� �ö󰡴� ����. ����϶��� �� ���� ����� ���߷��� �׸�ŭ �÷��ְ� �����ϋ��� �׸�ŭ ���� ���� ���� ���߷��� ��Ƴ�
				skillTime.restart();//��ų�� ���� ���� ����Ʈ�� ���ӵǴ� �ð��� �����ϴ� �ð�����

				sceneNum=playerSkill;

				if(!isMiss){//�̽��� ���� �ʾ��� ��� ��Ʈ/�߰� ����/�߰� ���߷��� ������
					//�߰� ���߷�
					if(skill->data[useSkillNow].plusAcc > 0)
						(*player)->setAcc(skill->data[useSkillNow].plusAcc);//�߰� ���߷��� ������
					else if(skill->data[useSkillNow].plusAcc < 0)
						enemy->setAcc(enemy->getAcc()+skill->data[useSkillNow].plusAcc);//���߷��� -�� : ���� ���߷��� �� ����ŭ ����ٴ� ���̴�.
					//�߰� ����
					if(skill->data[useSkillNow].guard > 0)
						(*player)->setGuard((*player)->getGuard()+skill->data[useSkillNow].guard);//�߰� ������ ������
					//��Ʈ��. �̰� ������ ����Ǵϱ� ������ �߰�����
					if(skill->data[useSkillNow].dot.damage > 0)
						enemy->addDot(skill->data[useSkillNow].dot);//��Ʈ���� ������ ������
					
				}
			}
		}
		if(canUseSkill[i] != 0){//������ ���� ������Ʈ
			if(i < (ViewSkill/2))
				tooltip[i]->setTooltip(skill->data[canUseSkill[i]].name, skill->data[canUseSkill[i]].effect, sf::FloatRect(836+(i*152),464,80,80), 350);//dir-------------------------->
			else
				tooltip[i]->setTooltip(skill->data[canUseSkill[i]].name, skill->data[canUseSkill[i]].effect, sf::FloatRect(836+((i-(ViewSkill/2))*152),593,80,80), 350);//dir-------------------------->
		}
		tooltip[i]->update();
	}

	hpGauge->update();
	enemyGauge->update();

	if(isBattle){//������ ���ѽð� ���úκ�. ���ѽð��� �Ѿ�� �÷��̾��� ���ݱ��� ��ǵǸ� ���� �ٷ� �� �ķ��Ҵ�. ���� ���� �ٷ��� �������� �ٷ� �װ���.
		timeGauge->update();//�� �������� ����Ÿ�� ������ �� ���ѽð��� �����ϴ� ����.
		if(puzzleTime.getElapsedTime().asSeconds() >= 0.1){
			puzzleTime.restart();
			timeGauge->setValue(-1);
			if(timeGauge->getValue() <= 0){
				sceneNum=enemySkill;
				skillTime.restart();

				if(enemy->getAcc() >= rand()%100){//�̽�����
					isMiss=false;
					if(rand()%100 <= enemy->getSubPro()){//���꽺ų �ߵ���
						subSkill=true;
						particle->setParticle(enemy->getSubAni(),skill->data[enemy->getSubAni()].soundLink,true);
						if(skill->data[enemy->getSubAni()].dot.damage > 0)
							(*player)->addDot(skill->data[enemy->getSubAni()].dot);//�÷��̾�� ��Ʈ��
					}else{//�� ��Ÿ ������
						particle->setParticle(enemy->getAnimationNum(),enemy->getSoundLink(),true);//��ƼŬ ����
					}
				}else{
					isMiss=true;
					particle->setParticle(100,"sounds/skill/miss.ogg",true);
				}
				enemy->setAcc(enemy->getMaxAcc());//�÷��̾ ��ų�� ���� ���߷��� ��������� (���� �� ���߷������� ��������Ƿ�) �ٽ� ������� ������
			}
		}
	}
}
void Battle::playerSkillUpdate(){
	if(particle->isEnd()){//��ƼŬ�� ���� ���
		skillTime.restart();
		int damage=skill->data[useSkillNow].damage*puzzle->getPlusDamage();//������ �ִ� ������
		int pdamage=skill->data[useSkillNow].pdamage;//���� ���� ������(�� ��ų�� ���� ������)

		//-------
		if(!isMiss){
			if(pdamage > 0){//�� ü�� ����
				if(pdamage >= (*player)->getGuard()){//�߰� ������ �� �ո� ���
					pdamage-=(*player)->getGuard();
					(*player)->setGuard(0);
				}else{//�߰� �������� ��Ⱑ �Ǵ°��
					(*player)->setGuard((*player)->getGuard()-pdamage);
					pdamage=0;
				}
				if(pdamage > (*player)->getHP()){//�°� ������ ���
					hpGauge->setValue(-1*(*player)->getHP());
					(*player)->setHP(0);
				}else{//�¾Ƶ� ���״� ���
					hpGauge->setValue(-1*pdamage);
					(*player)->setHP((*player)->getHP()-pdamage);
				}
			}else if(pdamage < 0){//�� ü�� ����
				if(-1*pdamage > (*player)->getMaxHP()-(*player)->getHP()){//ü��ȸ������ Ǯ�ǳ� �� �̻��� �Ǵ°��
					hpGauge->setValue((*player)->getMaxHP()-(*player)->getHP());
					(*player)->setHP((*player)->getMaxHP());
				}else{//�� ȸ��
					hpGauge->setValue(-1*pdamage);
					(*player)->setHP((*player)->getHP()-pdamage);
				}
			}
			if(damage > 0){//�� ü�� ����
				if(damage > enemy->getCurrentHp()){//���� ���뺸�� �������� Ŭ ���
					enemyGauge->setValue(-1*enemy->getCurrentHp());
					enemy->setCurrentHp(0);
				}else{//�� ������
					enemyGauge->setValue(-1*damage);
					enemy->setCurrentHp(enemy->getCurrentHp()-damage);
				}
				//---
				puzzle->setPlusDamage(1.0);//���ʽ� �������� ������ �������� �������� ���ǵ��� �س���.
			}else if(damage < 0){//�� ü�� ȸ��(�� ��ų�� ȿ����...)
				if(-1*damage > enemy->getMaxHp()-enemy->getCurrentHp()){//���� Ǯ�ǵǴ� ���
					enemyGauge->setValue(enemy->getMaxHp()-enemy->getCurrentHp());
					enemy->setCurrentHp(enemy->getMaxHp());
				}else{//�� ȸ��
					enemyGauge->setValue(-1*damage);
					enemy->setCurrentHp(enemy->getCurrentHp()-damage);
				}
			}
		}//�̽��� ���� ���� �� ��츦 �� ��ŵ��(�ƹ� ȿ�� �����ϱ�)
		if((*player)->getHP() <= 0 || enemy->getCurrentHp() <= 0)//���̳� ���� ���
			sceneNum=checkSkill;
		else{//���� ������ �Ѿ
			sceneNum=enemySkill;
			
			if(enemy->getAcc() >= rand()%100){//���� ������ ������
				isMiss=false;
				if(rand()%100 <= enemy->getSubPro()){//���� ���꽺ų ���
					subSkill=true;
					particle->setParticle(enemy->getSubAni(),skill->data[enemy->getSubAni()].soundLink,true);//��ƼŬ ����.
					if(skill->data[enemy->getSubAni()].dot.damage > 0)
						(*player)->addDot(skill->data[enemy->getSubAni()].dot);//�÷��̾�� ��Ʈ��. ���� �÷��̾ ���� ��Ʈ��ġ�� �� ��ų�� ��Ʈ���� �����ش�.
					//����� ���Ͱ� �÷��̾��� ��ų�� �貸������
					//��Ʈ��, �Ϲݵ� ���� ȿ��(���߷� ����/������ ���) ���� ��� �Ұ�
				}else{//���� ��Ÿ���
					particle->setParticle(enemy->getAnimationNum(),enemy->getSoundLink(),true);
				}
			}else{
				isMiss=true;
				particle->setParticle(100,"sounds/skill/miss.ogg",true);
			}
			enemy->setAcc(enemy->getMaxAcc());//������ ����� ���߷� ���� ���� Ǯ���ش�.
		}
	}
	hpGauge->update();
	enemyGauge->update();
	return;
}
void Battle::enemySkillUpdate(){//���� ��
	if(particle->isEnd()){//��ƼŬ�� �������
		int damage;//���� ������ �� ������
		if(subSkill){//���꽺ų ���ÿ� �� ��ų�� ������, �ƴϸ� ���� ������ ��Ÿ��
			damage = skill->data[enemy->getSubAni()].damage;
		}else{
			damage = enemy->getDamage();
		}
		
		if(!isMiss){//�̽��� �� ���� ������ ����� ��ŵ�ȴ�.
			if(damage >= (*player)->getGuard()){//�÷��̾��� �߰� ������ �վ������
				damage-=(*player)->getGuard();
				(*player)->setGuard(0);
			}else{//�߰��� ���� ���Ͽ������
				(*player)->setGuard((*player)->getGuard()-damage);
				damage=0;//�������� 0�̵�
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
	std::vector<Dot> _dot;
	//��Ʈ�� ���.

	//���Ⱑ ��Ʈ���� ����ϴ� ����.
	//������ ��Ʈ�� ����� : ���� �������� �߰��ǰ� �ϸ��� �׸�ŭ ����. �� �������� �ϸ��� 5�� ����
	//�����ҽÿ��� ��Ʈ���� ���ӵǴ� ������ �ϰ� ��ø�� ���� ��� �Ѵٴ��� �ϸ� �ɰŰ���
	//�Ͽ�ư ���⼭ ��� ��Ʈ���� ����ϸ� ��.

	if(enemy->getDot().size() > 0){//���� ���� ��Ʈ ����� �������� ������ �ϰ� 5�� �����. 
		_dot=enemy->getDot();
		for(int i=0;i<_dot.size();i++){
			if(_dot[i].damage > enemy->getCurrentHp()){
				enemyGauge->setValue(-1*enemy->getCurrentHp());
				enemy->setCurrentHp(0);
			}else{
				enemyGauge->setValue(-1*_dot[i].damage);
				enemy->setCurrentHp(enemy->getCurrentHp()-_dot[i].damage);
			}
		}
		enemy->updateDot();//��Ʈ�� ����ְ� �໡ �������� �����
	}
	if((*player)->getDot().size() > 0){//���� ����.
		_dot=(*player)->getDot();
		for(int i=0;i<_dot.size();i++){
			if(_dot[i].damage > (*player)->getHP()){
				hpGauge->setValue(-1*(*player)->getHP());
				(*player)->setHP(0);
			}else{
				hpGauge->setValue(-1*_dot[i].damage);
				(*player)->setHP((*player)->getHP()-_dot[i].damage);
			}
		}
		(*player)->updateDot();
	}
	//���� ���� ���� �ʱ�ȭ��Ʈ
	isMiss=false;
	subSkill=false;
	sceneNum=normal;
	timeGauge->setValue(puzzleLimit-timeGauge->getValue());
	return;
}
bool Battle::getResult(){//���⼭ ������ ���� ��� kill ī��Ʈ�� 1 �ø���(���� �̰����� �ȰŰ� ���� ������ Ÿ��Ʋ�Ű��� ���µ�)

	if(sceneNum != normal)
		return 0;
	if((*player)->getHP() <= 0){
		isBattle=false;
		puzzle->cleanStack();
		hpGauge->setValue(hpGauge->getValue()*-1);
		hpGauge->update();

		killEnemyNum++;
		return 1;
	}
	if(enemy->getCurrentHp() <= 0){
		isBattle=false;
		//���⼭ �÷��̾�� ���� ��Ʈ������ ������!
		(*player)->clearDot();
		enemy->clearDot();

		puzzle->cleanStack();
		enemyGauge->setValue(enemyGauge->getValue()*-1);
		enemyGauge->update();

		killEnemyNum++;
		return 1;
	}
	return 0;
}

void Battle::draw(sf::RenderWindow &window){
	int i;

	if(sceneNum == playerSkill || sceneNum == enemySkill){
		//if(!isMiss){//���� ���￹��(�̽����� ��ƼŬ �߰�)
		particle->draw(window);
		//return;
	}
	
	if(isBattle){
		window.draw(skillBGSprite);
		puzzle->draw(window);
		timeGauge->draw(window);
		
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
		window.draw(text);//���ʽ���,���߷�����,����,��Ʈ�� ��ġ �����ϴ� ��.
		window.draw(eText);//���� ��Ÿ ���߷��� ��Ʈ������ ���
		//---------------
		sf::Text vecterText,numText;
		std::vector<Dot> _dot;
		char vecNum[100];

		vecterText.setFont(font);
		numText.setFont(font);

		_dot=(*player)->getDot();
		if(_dot.size() > 0){
			for(int i=0;i<_dot.size();i++){
				status.setPosition(160+(i*30),630);
				status.setTextureRect(statusTileset->getTileSet(_dot[i].code-1));
				window.draw(status);
			}
			for(int i=0;i<_dot.size();i++){
				_snprintf(vecNum, sizeof(vecNum), "%d damage | %d Turn",_dot[i].damage,_dot[i].turn);
				numText.setString(vecNum);
				vecterText.setString(_dot[i].name);
				//-----
				pStatusTip[i]->setTooltip(vecterText.getString(), numText.getString(), sf::FloatRect(160+(i*30),630,25,25),350);
				pStatusTip[i]->draw(window);
			}
		}
		_dot=enemy->getDot();
		if(_dot.size() > 0){
			for(int i=0;i<_dot.size();i++){
				status.setPosition(460+(i*30),80);
				status.setTextureRect(statusTileset->getTileSet(_dot[i].code-1));
				window.draw(status);
			}
			for(int i=0;i<_dot.size();i++){
				_snprintf(vecNum, sizeof(vecNum), "%d damage | %d Turn",_dot[i].damage,_dot[i].turn);
				numText.setString(vecNum);
				vecterText.setString(_dot[i].name);
				//---
				eStatusTip[i]->setTooltip(vecterText.getString(),numText.getString(),sf::FloatRect(460+(i*30),80,25,25),350);
				eStatusTip[i]->draw(window);
			}
		}
		enemyGauge->draw(window);
		window.draw(enemy->getName());//�� �̸� ���!
	}
		
	hpGauge->draw(window);
	//---face---//
	faceSprite.setTextureRect(faceTileset->getTileSet((100-(*player)->getHP())/20));
	window.draw(faceSprite);
	//---
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
Puzzle* Battle::getPuzzle(){
	return puzzle;
}
void Battle::setGaugeMax(){
	hpGauge->setValue(100-hpGauge->getValue());
}