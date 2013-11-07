#include "particlelist.h"

ParticleList::ParticleList(int _x, int _y){
	x=_x;
	y=_y;
	particle = new particle::FireBall(x,y);
}
void ParticleList::setParticle(int _num){
	num=_num;
	switch(num){
		case 1: //화염구
			delete particle;
			particle = new particle::FireBall(x,y);
			break;
		case 2: //타오르는 화염
			delete particle;
			particle = new particle::Explosion(x,y);
			break;
		case 3://임시 : 불의 비
			delete particle;
			particle = new particle::FireRain(x,y);
			break;
		case 5: //기우제
			delete particle;
			particle = new particle::Rain(x,y);
			break;
		case 6: //침수
			delete particle;
			particle = new particle::Water(x,y);
			break;
		case 100: //몹 공격 1번?
			delete particle;
			particle = new particle::Cut(x,y);
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
	particle->setLocationList();
}