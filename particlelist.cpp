#include "particlelist.h"

ParticleList::ParticleList(int _x, int _y){
	x=_x;
	y=_y;
	particle = new particle::Fire(x,y);//걍 적당히 초기화? 글쎼
}
void ParticleList::setParticle(int _num){
	num=_num;
	switch(num){
		case 1: //화염구
			delete particle;
			particle = new particle::Fire(x,y);			
			break;
		case 2: //타오르는 화염
			delete particle;
			particle = new particle::Explosion(x,y);
			break;
		case 100: //몹 공격 1번?
			delete particle;
			particle = new particle::Water(x,y);
			break;
		default : 
			delete particle;
			particle = new particle::Explosion(x,y);
	}
}
ParticleList::~ParticleList(){
	delete particle;
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
			particle->setLocation(sf::Vector2i(500,250));
			particle->setLocationVar(sf::Vector2i(650,280));
			particle->fuelInSequence(0.0, 10);
			break;
		case 2 : 
			particle->setLocation(sf::Vector2i(0,0));
			particle->setLocationVar(sf::Vector2i(1280,700));
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