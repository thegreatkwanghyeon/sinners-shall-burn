#include "player.h"


Player::Player(){
	skill = new Skill();

	for(int i=0;i<7;i++){//�⺻ ����
		element[i]=1;
		useElement[i]=i;
	}
	for(int i=0;i<skill->skillNum;i++)
		skill->setHave(i);

	hp=100;
	maxHp=100;
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
std::vector<Dot> Player::getDot(){
	return dot;
}
void Player::addDot(Dot _dot){
	for(int i=0;i<dot.size();i++){
		if(dot[i].code == _dot.code){
			dot[i].turn+=_dot.turn;
			if(dot[i].damage < _dot.damage)
				dot[i].damage=_dot.damage;
			return;
		}
	}
	dot.push_back(_dot);
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
void Player::updateDot(){
	for(int i=0;i<dot.size();i++){
		dot[i].turn--;
		if(dot[i].turn <= 0){
			dot.erase(dot.begin()+i);
		}
	}
}
void Player::clearDot(){
	dot.clear();
}	