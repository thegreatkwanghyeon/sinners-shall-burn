#include "particlelist.h"

ParticleList::ParticleList(int x, int y){
	particle = new ParticleSystem(x, y);
}
void ParticleList::setParticle(int _num){
	num=_num;
	switch(num){
		case 1: //È­¿°±¸
			particle->setTexture("img/particles/circle.png");
			particle->setAngle(70);
			particle->setAngleVar(110);
			particle->setLife(90);
			particle->setLifeVar(130);
			particle->setSpeed(0.4);
			particle->setSpeedVar(0.6);
			particle->setStartColor(255, 180, 0, 255);
			particle->setEndColor(255, 0, 0, 0);
			break;
		case 100: //¸÷ °ø°Ý 1¹ø?
			particle->setTexture("img/particles/circle.png");
			particle->setAngle(0);
			particle->setAngleVar(360);
			particle->setLife(90);
			particle->setLifeVar(130);
			particle->setSpeed(0.4);
			particle->setSpeedVar(0.6);
			particle->setStartColor(0, 180, 255, 255);
			particle->setEndColor(0, 0, 255, 0);
			break;
		default : 
			particle->setTexture("img/particles/circle.png");
			particle->setAngle(70);
			particle->setAngleVar(110);
			particle->setLife(90);
			particle->setLifeVar(130);
			particle->setSpeed(0.4);
			particle->setSpeedVar(0.6);
			particle->setStartColor(255, 180, 0, 255);
			particle->setEndColor(255, 0, 0, 0);
	}
}
void ParticleList::update(){
	particle->update();
}

void ParticleList::draw(sf::RenderWindow &window){
	particle->draw(window);
}
void ParticleList::setLocationList(){
	switch(num){
		case 1: 
			particle->setLocation(sf::Vector2i(550,250));
			particle->setLocationVar(sf::Vector2i(880,280));
			particle->fuelInSequence(0.0, 10);
			break;
		case 100 : 
			particle->setLocation(sf::Vector2i(550,350));
			particle->setLocationVar(sf::Vector2i(580,380));
			particle->fuelInSequence(0.0, 10);
			break;
		default : 
			particle->setLocation(sf::Vector2i(550,250));
			particle->setLocationVar(sf::Vector2i(880,280));
			particle->fuelInSequence(0.0, 10);
	}
}