#include "enemy.h"

Enemy::Enemy() : textureSize(64){

}

Enemy::Enemy(int _code) : textureSize(256){
	enemyData.LoadFile("xmls/enemies.xml");
	TiXmlNode *pNode = enemyData.FirstChildElement("Enemies")->FirstChildElement("Enemy");

	for(int i=0;;i++){
		int tmpCode;
		pNode->ToElement()->Attribute("code",&tmpCode);

		if(tmpCode == _code){
			pNode->ToElement()->Attribute("hp",&maxHp);
			currentHp = maxHp;
			pNode->ToElement()->Attribute("damage",&damage);
			pNode->ToElement()->Attribute("acc",&acc);
			maxAcc=acc;
			pNode->ToElement()->Attribute("skill1",&animationNum);
			pNode->ToElement()->Attribute("skill2",&subAniNum);
			pNode->ToElement()->Attribute("subpro",&subPro);
			textureName=(MTW(pNode->ToElement()->Attribute("imgLink")));
			soundLink=(MTW(pNode->ToElement()->Attribute("soundLink")));
			name.setString(MTW(pNode->ToElement()->Attribute("name")));
			intro=(MTW(pNode->ToElement()->GetText()));
			code=tmpCode;
			break;
		}else if(tmpCode > _code){
			return;
		}

		pNode = pNode->NextSibling();
	}
	//임시
	position = sf::Vector2f(0.0f, 0.0f);
	dot=0;

	font.loadFromFile("font/spike.ttf");
	name.setFont(font);
	name.setPosition(450,200);
}

Enemy::~Enemy(){

}

sf::Text Enemy::getName(){
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

//임시
void Enemy::setPosition(sf::Vector2f position){
	this->position = position;
}

void Enemy::setTexture(sf::Image texture){
	this->texture = texture;
	this->convertedTexture = convertImageToTexture(texture);
}
int Enemy::getDot(){
	return dot;
}
void Enemy::setDot(int num){
	dot=num;
}
int Enemy::getAcc(){
	return acc;
}
int Enemy::getSubPro(){
	return subPro;
}
int Enemy::getSubAni(){
	return subAniNum;
}
int Enemy::getMaxAcc(){
	return maxAcc;
}
void Enemy::setAcc(int num){
	acc=num;
}
sf::String Enemy::getTextureName(){
	return textureName;
}
sf::String Enemy::getIntro(){
	return intro;
}
sf::String Enemy::getSoundLink(){
	return soundLink;
}