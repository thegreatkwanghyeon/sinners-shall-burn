#include "enemy.h"

Enemy::Enemy(){

}

Enemy::Enemy(int code){
	enemyData.LoadFile("xmls/enemies.xml");
	TiXmlNode *pNode = enemyData.FirstChildElement("Enemies")->FirstChildElement("Enemy");

	for(int i=0;;i++){
		int tmpCode;
		pNode->ToElement()->Attribute("code",&tmpCode);

		if(tmpCode == code){
			pNode->ToElement()->Attribute("hp",&maxHp);
			currentHp = maxHp;
			name = MTW(pNode->ToElement()->GetText());
			code=i; break;
		}else if(tmpCode > code){
			return;
		}

		pNode = pNode->NextSibling();
	}

	//юс╫ц
	position = sf::Vector2f(0.0f, 0.0f);
}

Enemy::~Enemy(){

}

sf::String Enemy::getName(){
	return name;
}
int Enemy::getMaxHp(){
	return maxHp;
}
int Enemy::getCurrentHp(){
	return currentHp;
}
sf::Vector2f Enemy::getPosition(){
	return position;
}
sf::Sprite Enemy::getSprite(){
	return sprite;
}