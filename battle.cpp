#include "battle.h"
#include <string.h>

Battle::Battle(){
	int i;
	puzzle = new Puzzle();

	stats.LoadFile("xmls/Monster.xml");
	font.loadFromFile("font/spike.ttf");
	TiXmlNode *pNode = stats.FirstChildElement("Monster")->FirstChildElement("Enemy");

	for(i=0;i<=3;i++){
		list[i].name.setString(MTW(pNode->ToElement()->GetText()));		
		pNode->ToElement()->Attribute("hp",&list[i].status[0]);

		printf("hp : %d\n",list[i].status[0]);

		list[i].name.setFont(font);
		list[i].name.setString(MTW(pNode->ToElement()->GetText()));
		list[i].name.setColor(sf::Color(255,255,255,255));
		list[i].name.setPosition(400.0f,400.0f+(30*i));
		pNode = pNode->NextSibling();
	}	
}

void Battle::update(sf::Event &event){
	puzzle->update();
}

void Battle::draw(sf::RenderWindow &window){
	puzzle->draw(window);
	window.draw(list[0].name);
	window.draw(list[1].name);
	window.draw(list[2].name);
	window.draw(list[3].name);
}