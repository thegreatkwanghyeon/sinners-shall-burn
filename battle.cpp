#include "battle.h"
#include <string.h>

Battle::Battle(int Code, Player* player){
	int i;
	int tp;
	puzzle = new Puzzle();
	puzzle->setElement(player->useElement);

	tileset = new TileSet();
	texture.loadFromFile("img/skill2.png");
	printf("???");
	texture = tileset->tileSet("img/skill2.png",30,30);
	sprite.setTexture(texture);
	sprite.setTextureRect(tileset->getTileSet(0));

	for(i=0;i<ViewSkill;i++){
		canUseSkill[i]=0;
		button[i] = new Button("img/sbutton.png");
		button[i]->setPosition(10,300+i*55);
		//button->setText("HINT", 18);
	}

	skill = player->skill;

	stats.LoadFile("xmls/Monster.xml");
	font.loadFromFile("font/spike.ttf");
	TiXmlNode *pNode = stats.FirstChildElement("Monster")->FirstChildElement("Enemy");

	

	for(i=0;;i++){
		pNode->ToElement()->Attribute("code",&tp);
		if(tp == Code){
			monster.name.setString(MTW(pNode->ToElement()->GetText()));
			pNode->ToElement()->Attribute("hp",&monster.status[hp]);
			pNode->ToElement()->Attribute("attack",&monster.status[attack]);
			pNode->ToElement()->Attribute("defense",&monster.status[defense]);
			pNode->ToElement()->Attribute("critical",&monster.status[critical]);
			pNode->ToElement()->Attribute("agility",&monster.status[agility]);
			pNode->ToElement()->Attribute("accuracy",&monster.status[accuracy]);

			monster.name.setFont(font);
			monster.name.setString(MTW(pNode->ToElement()->GetText()));
			monster.name.setColor(sf::Color(255,255,255,255));
			monster.name.setPosition(400.0f,400.0f+(30*i));

			code=i;
			break;
		}else if(tp > Code){
			printf("I Can't find Code...");
			return;
		}
		
		pNode = pNode->NextSibling();
	}
	/*
	stats.LoadFile("xmls/skill.xml");
	pNode = stats.FirstChildElement("List")->FirstChildElement("skill");

	for(i=0;;i++){
		for(j=0;j<30;j++){
			skill[i].need[j]=0;
			skill[i].Estat[j]=0;
			skill[i].Pstat[j]=0;
		}
		skill[i].use=false;
		pNode->ToElement()->Attribute("code",&skill[i].code);
		//printf("%d\n",skill[i].code);

		skill[i].name.setString(MTW(pNode->ToElement()->Attribute("name")));
		skill[i].intro.setString(MTW(pNode->ToElement()->Attribute("intro")));
		skill[i].effect.setString(MTW(pNode->ToElement()->GetText()));
		pNode->ToElement()->Attribute("damage",&skill[i].damage);
		pNode->ToElement()->Attribute("poison",&skill[i].poison);
		pNode->ToElement()->Attribute("heal",&skill[i].heal);

		pNode->ToElement()->Attribute("Estat",&tp);
		translate(tp,skill[i].Estat);
		pNode->ToElement()->Attribute("Pstat",&tp);
		translate(tp,skill[i].Pstat);
		pNode->ToElement()->Attribute("need",&skill[i].needCode);
		translate(skill[i].needCode,skill[i].need);
		
		if(pNode->NextSibling() == NULL)
			break;
		pNode = pNode->NextSibling();
	}
	skillNum=i+1;*/
}

void Battle::update(sf::Event &event){
	int i,j,k;
	int temp;//�ڵ尪 �ӽ� �����
	int useCnt=0;
	int chk[200]={0,};

	//for(i=0;i<skill->skillNum;i++)
	//	skill->data[i].use = false;

	puzzle->update(event);
	/*if(puzzle->hitNum > 5){
		printf("���� ��...���� �ð� �ʰ�");
	}*/
	for(i=0;i<ViewSkill;i++)
		canUseSkill[i]=0;
	for(i=0;i<200;i++){
		chk[i]=0;
	}

	for(i=StackNum;i>=1;i--){
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
		if(canUseSkill[i] != 0 && button[i]->checkMouseClick(event)){
			useSkill(canUseSkill[i]);
		}
	}


	//for(i=0;i<skill->skillNum;i++){
		//if(skill->data[i].use == true)
			//printf("No.%d\n",i);
	//}

	//��밡�� ��ų �˻�
	//��ų ���. ������ ���
	//�ߵ�/��/�������� ���� ���
	//��ų ����߰ų� ��ó�� 5 ������ ���͵� ����
	//�ߵ�/��/�������� ���� ���
	//�������. ���� ������ �÷��׸� �����ؼ� �Ʒ� �ٸ���Ʈ�� �Ҽ��ְ� ��
}
int Battle::GetResult(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		return -1;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		return 1;
	return 0;
}

void Battle::draw(sf::RenderWindow &window){
	int i;
	puzzle->draw(window);
	window.draw(monster.name);

	for(i=0;i<ViewSkill;i++){
		button[i]->draw(window);
	}
	for(i=0;i<ViewSkill;i++){
		sprite.setPosition(150,310+i*55);
		sprite.setTextureRect(tileset->getTileSet(canUseSkill[i]));
		window.draw(sprite);
	}
}
int Battle::makeCode(int s, int e){
	int i,re=1;

	if(e >= StackNum)
		return -1;
	for(i=s;i<e;i++){
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