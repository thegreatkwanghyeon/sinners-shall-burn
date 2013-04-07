#include "skill.h"
#include <string.h>

Skill::Skill(){
	int i,j;
	int tp;

	xmls.LoadFile("xmls/skill.xml");
	TiXmlNode *pNode = xmls.FirstChildElement("List")->FirstChildElement("skill");

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
		for(j=0;j<30;j++){
			data[i].need[j]=0;
			data[i].Estat[j]=0;
			data[i].Pstat[j]=0;
		}
		data[i].use=false;
		pNode->ToElement()->Attribute("code",&data[i].code);
		//printf("%d\n",skill[i].code);

		data[i].name.setString(MTW(pNode->ToElement()->Attribute("name")));
		data[i].intro.setString(MTW(pNode->ToElement()->Attribute("intro")));
		data[i].effect.setString(MTW(pNode->ToElement()->GetText()));
		pNode->ToElement()->Attribute("damage",&data[i].damage);
		pNode->ToElement()->Attribute("poison",&data[i].poison);
		pNode->ToElement()->Attribute("heal",&data[i].heal);
		pNode->ToElement()->Attribute("distance",&data[i].distance);
		pNode->ToElement()->Attribute("distanceACK",&data[i].distanceACK);
		pNode->ToElement()->Attribute("guard",&data[i].guard);
		pNode->ToElement()->Attribute("field",&data[i].field);
		pNode->ToElement()->Attribute("acc",&data[i].acc);


		pNode->ToElement()->Attribute("Estat",&tp);
		translate(tp,data[i].Estat);
		pNode->ToElement()->Attribute("Pstat",&tp);
		translate(tp,data[i].Pstat);
		pNode->ToElement()->Attribute("need",&data[i].needCode);
		translate(data[i].needCode,data[i].need);
		
		if(pNode->NextSibling() == NULL)
			break;
		pNode = pNode->NextSibling();
	}
	skillNum=i+1;
}

void Skill::translate(int num, int m[]){
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
void Skill::setHave(int num){
	int i;
	for(i=0;i<skillNum;i++){
		if(data[i].have == false && data[i].code == num)
			data[i].have = true;
	}
}