#include "skilleffect.h"

SkillEffect::SkillEffect(){
	end = false;
}

SkillEffect::~SkillEffect(){

}

void SkillEffect::update(){
	time = clock.getElapsedTime().asSeconds();
	clock.restart();
}

void SkillEffect::draw(sf::RenderWindow &window){

}

void SkillEffect::setEnd(){
	end = true;
}
