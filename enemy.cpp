#include "enemy.h"

Enemy::Enemy(){

}

Enemy::Enemy(int _code){
	enemyData.LoadFile("xmls/enemies.xml");
	TiXmlNode *pNode = enemyData.FirstChildElement("Enemies")->FirstChildElement("Enemy");

	for(int i=0;;i++){
		int tmpCode;
		pNode->ToElement()->Attribute("code",&tmpCode);

		if(tmpCode == _code){
			pNode->ToElement()->Attribute("hp",&maxHp);
			currentHp = maxHp;
			pNode->ToElement()->Attribute("damage",&damage);
			name = MTW(pNode->ToElement()->GetText());
			code=tmpCode;
			break;
		}else if(tmpCode > _code){
			return;
		}

		pNode = pNode->NextSibling();
	}

	//임시
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
int Enemy::getAnimationNum(){
	return animationNum;
}
int Enemy::getDamage(){
	return damage;
}
void Enemy::setCurrentHp(int num){
	currentHp=num;
}
sf::Vector2f Enemy::getPosition(){
	return position;
}
sf::Sprite Enemy::getSprite(){
	return sprite;
}

int Enemy::getCode(){
	return code;
}

//임시
void Enemy::setPosition(sf::Vector2f position){
	this->position = position;
}

void Enemy::setTexture(sf::Texture texture){
	this->texture = texture;
}