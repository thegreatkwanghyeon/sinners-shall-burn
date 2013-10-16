#include "player.h"


Player::Player(){
	skill = new Skill();

	for(int i=0;i<7;i++){//기본 원소
		element[i]=1;
		useElement[i]=i;
	}
	skill->setHave(1);
	skill->setHave(2);
	skill->setHave(3);
	skill->setHave(4);
	skill->setHave(5);

	hp=100;
	maxHp=100;
}

void Player::update(){
	
}

void Player::draw(sf::RenderWindow &window){

}
int Player::getHP(){
	return hp;
}
void Player::setHP(int num){
	hp=num;
}
int Player::getMaxHP(){
	return maxHp;
}
void Player::setMaxHP(int num){
	maxHp=num;
}