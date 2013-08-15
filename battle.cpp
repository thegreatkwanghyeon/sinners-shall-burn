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

	for(i=0;i<ViewSkill;i++){
		canUseSkill[i]=0;
		button[i] = new Button("img/sbutton.png");
		button[i]->setPosition(10,300+i*55);
		//button->setText("HINT", 18);
		tooltip[i] = new Tooltip("img/tooltip.png");
		tooltip[i]->setTooltip(L"디폴트", L"디폴트", sf::FloatRect(150,310+i*55,30,30), 350);
	}
}

void Battle::update(sf::Event &event){
	int i,j,k;
	int temp;//코드값 임시 저장소
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
			useSkill(canUseSkill[i]);
			deltaClock.restart();
			keyEvent=true;
		}
		if(canUseSkill[i] != 0)			
			tooltip[i]->setTooltip(skill->data[canUseSkill[i]].name, skill->data[canUseSkill[i]].effect, sf::FloatRect(150,310+i*55,30,30), 350);
		//else 
		//	tooltip[i]->setTooltip(L"디폴트", L"디폴트", sf::FloatRect(150,310+i*55,30,30), 350);
		tooltip[i]->update();
	}


	//for(i=0;i<skill->skillNum;i++){
		//if(skill->data[i].use == true)
			//printf("No.%d\n",i);
	//}

	//사용가능 스킬 검사
	//스킬 사용. 데미지 계산
	//중독/힐/스탯저하 등을 계산
	//스킬 사용했거나 위처럼 5 넘으면 몬스터도 공격
	//중독/힐/스탯저하 등을 계산
	//사망판정. 누구 죽으면 플래그를 조정해서 아래 겟리술트를 할수있게 함
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
		tooltip[i]->draw(window);
	}
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