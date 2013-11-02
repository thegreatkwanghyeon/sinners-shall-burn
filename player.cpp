#include "player.h"


Player::Player(){
	skill = new Skill();

	for(int i=0;i<7;i++){//기본 원소
		element[i]=1;
		useElement[i]=i;
	}
	for(int i=0;i<skill->skillNum;i++)
		skill->setHave(i);

	hp=100;
	maxHp=100;
	dot=0;
	acc=0;
	guard=0;
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
int Player::getDot(){
	return dot;
}
void Player::setDot(int num){
	dot=num;
}
int Player::getAcc(){
	return acc;
}
void Player::setAcc(int num){
	acc=num;
}
int Player::getGuard(){
	return guard;
}
void Player::setGuard(int num){
	guard=num;
}