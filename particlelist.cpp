#include "particlelist.h"

ParticleList::ParticleList(int _x, int _y){
	x=_x;
	y=_y;
	for(int i=0;i<5;i++)
		particle[i] = new particle::Fire(x,y);
	useNum=0;
}
void ParticleList::setParticle(int _num){
	num=_num;
	switch(num){
		case 1: //화염구
			delete particle[0];
			particle[0] = new particle::Fire(x,y);		
			useNum=1;
			break;
		case 2: //타오르는 화염
			delete particle[0];
			particle[0] = new particle::Explosion(x,y);
			useNum=1;
			break;
		case 5: //기우제
			delete particle[0];
			particle[0] = new particle::Rain(x,y);
			useNum=1;
			break;
		case 6: //침수
			delete particle[0];
			particle[0] = new particle::Water(x,y);
			useNum=1;
			break;
		case 100: //몹 공격 1번?
			delete particle[0];
			delete particle[1];
			particle[0] = new particle::Water(x,y);
			particle[1] = new particle::Fire(x,y);
			useNum=2;
			break;
		default : 
			delete particle[0];
			particle[0] = new particle::Explosion(x,y);
			useNum=1;
	}
}
ParticleList::~ParticleList(){
	delete particle;
}
void ParticleList::update(){
	for(int i=0;i<useNum;i++)
		particle[i]->update();
}

void ParticleList::draw(sf::RenderWindow &window){
	for(int i=0;i<useNum;i++)
		particle[i]->draw(window);
}
void ParticleList::setLocationList(){
	switch(num){
		case 1: 
			particle[0]->setLocation(sf::Vector2i(500,250));
			particle[0]->setLocationVar(sf::Vector2i(650,280));
			particle[0]->fuelInSequence(0.0, 10);
			break;
		case 2 : 
			particle[0]->setLocation(sf::Vector2i(0,0));
			particle[0]->setLocationVar(sf::Vector2i(1280,700));
			particle[0]->fuelInSequence(0.0, 10);
			break;
		case 5 : 
			particle[0]->setLocation(sf::Vector2i(0,0));
			particle[0]->setLocationVar(sf::Vector2i(1280,700));
			particle[0]->fuelInSequence(0.0, 10);
			break;
		case 6 : 
			particle[0]->setLocation(sf::Vector2i(500,300));
			particle[0]->setLocationVar(sf::Vector2i(600,400));
			particle[0]->fuelInSequence(0.0, 10);
			break;
		case 100 : 
			particle[0]->setLocation(sf::Vector2i(550,350));
			particle[0]->setLocationVar(sf::Vector2i(580,380));
			particle[0]->fuelInSequence(0.0, 10);

			particle[1]->setLocation(sf::Vector2i(450,350));
			particle[1]->setLocationVar(sf::Vector2i(580,780));
			particle[1]->fuelInSequence(0.0, 10);
			break;
		default : 
			particle[0]->setLocation(sf::Vector2i(550,250));
			particle[0]->setLocationVar(sf::Vector2i(880,280));
			particle[0]->fuelInSequence(0.0, 10);
	}
}