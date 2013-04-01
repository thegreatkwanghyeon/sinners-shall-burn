#include "battle.h"
#include <string.h>

Battle::Battle(int Code, Player* player){
	int i,j;
	int tp;
	puzzle = new Puzzle();
	puzzle->setElement(player->useElement);

	stats.LoadFile("xmls/Monster.xml");
	font.loadFromFile("font/spike.ttf");
	TiXmlNode *pNode = stats.FirstChildElement("Monster")->FirstChildElement("Enemy");

	check[0]=2;
	tp=1;
	for(i=3;i<100;i+=2){
		for(j=3;j<=sqrt(i);j+=2){
			if(i%j == 0)
				break;
		}
		if(j > sqrt(i))
			check[tp++]=i;
	}

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
	skillNum=i+1;
}

void Battle::update(sf::Event &event){
	int i,j,k;
	int temp;//코드값 임시 저장소

	for(i=0;i<skillNum;i++)
		skill[i].use = false;

	puzzle->update();
	/*if(puzzle->hitNum > 5){
		printf("적의 턴...퍼즐 시간 초과");
	}*/

	for(i=1;i<=StackNum;i++){
		for(j=0;j+i<StackNum;j++){
			temp = makeCode(j,j+i);
			for(k=0;k<skillNum;k++){
				if(temp == skill[k].needCode){
					skill[k].use = true;
					break;
				}
			}
		}
	}

	for(i=0;i<skillNum;i++){
		if(skill[i].use == true)
			printf("No.%d\n",i);
	}

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
	puzzle->draw(window);
	window.draw(monster.name);
}
void Battle::translate(int num, int m[]){
	int i;
	bool flag=false;

	printf("num : %d\n",num);

	if(num == 0)
		return;
	if(num < 0){
		flag = true;
		num*=-1;
	}

	while(1){
		for(i=0;;i++){
			if(num%check[i] == 0)
				break;
		}
		num /= check[i];
		if(flag == true)
			m[i]--;
		else
			m[i]++;
		if(num <= 1)
			break;
	}
}
int Battle::makeCode(int s, int e){
	int i,re=1;

	if(e >= StackNum)
		return -1;
	for(i=s;i<e;i++){
		re *= check[puzzle->stack[i]->num];
	}
	return re;
}