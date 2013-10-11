#include "enemy.h"

Enemy::Enemy() : textureSize(64){

}

Enemy::Enemy(int _code) : textureSize(64){
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
	//�ӽ�
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

sf::Image Enemy::getTexture(){
	return texture;
}

std::vector<sf::Uint32> Enemy::convertImageToTexture(sf::Image image){
	sf::Color color;
	std::vector<sf::Uint32> texture;

	texture.resize(textureSize * textureSize);
	
	for(int x=0; x<textureSize; x++){
		for(int y=0; y<textureSize; y++){
			color = image.getPixel(x, y);
			texture[textureSize*y + x] = color.r * 65536 + color.g * 256 + color.b;	
		} 
	}
	return texture;
}

std::vector<sf::Uint32>* Enemy::getConvertedTexture(){
	return &convertedTexture;
}

//�ӽ�
void Enemy::setPosition(sf::Vector2f position){
	this->position = position;
}

void Enemy::setTexture(sf::Image texture){
	this->texture = texture;
	this->convertedTexture = convertImageToTexture(texture);
}