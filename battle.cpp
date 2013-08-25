#include "battle.h"
#include <string.h>

Battle::Battle(int Code, Player* player){
	int i;
	puzzle = new Puzzle();
	puzzle->setElement(player->useElement);

	tileset = new TileSet();
	texture.loadFromFile("img/skill2.png");
	texture = tileset->tileSet("img/skill2.png",30,30);
	sprite.setTexture(texture);
	sprite.setTextureRect(tileset->getTileSet(0));

	skill = player->skill;

	font.loadFromFile("font/spike.ttf");

	for(i=0;i<ViewSkill;i++){
		canUseSkill[i]=0;
		button[i] = new Button("img/sbutton.png");
		button[i]->setPosition(20,420+i*55);//dir-------------------------->
		//button->setText("HINT", 18);
		tooltip[i] = new Tooltip("img/tooltip.png");
		tooltip[i]->setTooltip(L"����Ʈ", L"����Ʈ", sf::FloatRect(70,430+i*55,30,30), 350);//dir-------------------------->
	}
	isBattle=false;

	hpGauge = new Gauge("img/hpgauge.png",100, 1, 1);
	hpGauge->setPosition(sf::Vector2i(0,0));

	enemyGauge = new Gauge("img/enemygauge.png",100,0,0);
	enemyGauge->setPosition(sf::Vector2i(357,150));
}
void Battle::startBattle(int code){
	int tp;
	stats.LoadFile("xmls/Monster.xml");
	TiXmlNode *pNode = stats.FirstChildElement("Monster")->FirstChildElement("Enemy");

	for(int i=0;;i++){
		pNode->ToElement()->Attribute("code",&tp);
		if(tp == code){
			monster.name.setString(MTW(pNode->ToElement()->GetText()));
			pNode->ToElement()->Attribute("hp",&monster.hp);

			monster.name.setFont(font);
			monster.name.setString(MTW(pNode->ToElement()->GetText()));
			monster.name.setColor(sf::Color(255,255,255,255));
			monster.name.setPosition((float)500,(float)120);

			code=i;
			break;
		}else if(tp > code){
			printf("I Can't find Code...");
			return;
		}
		pNode = pNode->NextSibling();
	}
	isBattle=true;
}

void Battle::update(sf::Event &event){
	int i,j,k;
	int temp;//�ڵ尪 �ӽ� �����
	int useCnt=0;
	int chk[200]={0,};

	float delta;

	puzzle->update(event);

	if(keyEvent){
		delta=deltaClock.getElapsedTime().asSeconds();
		if(delta >= 0.5)
			keyEvent=false;
	}

	for(i=0;i<ViewSkill;i++)
		canUseSkill[i]=0;
	for(i=0;i<200;i++){
		chk[i]=0;
	}

	for(i=StackNum-1;i>=0;i--){
		for(j=0;j+i<StackNum;j++){
			temp = makeCode(j,j+i);
			for(k=0;k<skill->skillNum;k++){
				if(temp == skill->data[k].needCode && useCnt < ViewSkill && chk[skill->data[k].code] == 0){
					//skill->data[k].use = true;
					chk[skill->data[k].code]=1;
					canUseSkill[useCnt++]=skill->data[k].code;
					break;
				}
			}
		}
	}

	for(i=0;i<ViewSkill;i++){
		button[i]->update(event);
		if(keyEvent == false && canUseSkill[i] != 0 && button[i]->checkMouseClick(event)){
			if(isBattle){
				useSkill(canUseSkill[i]);
				deltaClock.restart();
				keyEvent=true;
			}else{
				printf("������ �ƴ� �����\n");
			}
		}
		if(canUseSkill[i] != 0)			
			tooltip[i]->setTooltip(skill->data[canUseSkill[i]].name, skill->data[canUseSkill[i]].effect, sf::FloatRect(70,430+i*55,30,30), 350);//dir-------------------------->
		//else 
		//	tooltip[i]->setTooltip(L"����Ʈ", L"����Ʈ", sf::FloatRect(150,360+i*55,30,30), 350);
		tooltip[i]->update();
	}


	hpGauge->update();
	enemyGauge->update();

	//��밡�� ��ų �˻�
	//��ų ���. ������ ���
	//�ߵ�/��/�������� ���� ���
	//��ų ����߰ų� ��ó�� 5 ������ ���͵� ����
	//�ߵ�/��/�������� ���� ���
	//�������. ���� ������ �÷��׸� �����ؼ� �Ʒ� �ٸ���Ʈ�� �Ҽ��ְ� ��
}
int Battle::getResult(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
		isBattle=false;
		return -1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
		isBattle=false;
		return 1;
	}
	return 0;
}

void Battle::draw(sf::RenderWindow &window){
	int i;
	puzzle->draw(window);
	if(isBattle){
		window.draw(monster.name);
		enemyGauge->draw(window);
	}

	for(i=0;i<ViewSkill;i++){
		button[i]->draw(window);
	}
	for(i=0;i<ViewSkill;i++){
		sprite.setPosition(70,430+i*55);//dir-------------------------->
		sprite.setTextureRect(tileset->getTileSet(canUseSkill[i]));
		window.draw(sprite);
		tooltip[i]->draw(window);
	}
	hpGauge->draw(window);
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