#include "battle.h"
#include <string.h>

Battle::Battle(int Code){
	int i;
	int tp;
	puzzle = new Puzzle();

	stats.LoadFile("xmls/Monster.xml");
	font.loadFromFile("font/spike.ttf");
	TiXmlNode *pNode = stats.FirstChildElement("Monster")->FirstChildElement("Enemy");

	for(i=0;;i++){
		pNode->ToElement()->Attribute("code",&tp);
		printf("%d's Code : %d\n",i,tp);
		if(tp == Code){
			list[i].name.setString(MTW(pNode->ToElement()->GetText()));
			pNode->ToElement()->Attribute("hp",&list[i].status[0]);

			list[i].name.setFont(font);
			list[i].name.setString(MTW(pNode->ToElement()->GetText()));
			list[i].name.setColor(sf::Color(255,255,255,255));
			list[i].name.setPosition(400.0f,400.0f+(30*i));

			code=i;
			break;
		}else if(tp > Code){
			printf("I Can't find Code...");
			return;
		}
		
		pNode = pNode->NextSibling();
	}
}

void Battle::update(sf::Event &event){
	puzzle->update();
}

void Battle::draw(sf::RenderWindow &window){
	puzzle->draw(window);
	window.draw(list[code].name);
}