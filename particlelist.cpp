#include "particlelist.h"

ParticleList::ParticleList(int _x, int _y){
	x=_x;
	y=_y;
	particle = new particle::FireBall(x,y);
}
void ParticleList::setParticle(int _num){
	num=_num;
	switch(num){
		case 1: //È­¿°±¸
			delete particle;
			particle = new particle::FireBall(x,y);
			break;
		case 2: //Å¸¿À¸£´Â È­¿°
			delete particle;
			particle = new particle::Explosion(x,y);
			break;
		case 3://Áö¿ÁºÒ
			delete particle;
			particle = new particle::Fire(x,y);
			break;
		case 4://¼¼¸êÈ­
			delete particle;
			particle = new particle::FireRain2(x,y);
			break;
		case 5: //±â¿ìÁ¦
			delete particle;
			particle = new particle::Rain(x,y);
			break;
		case 6: //Ä§¼ö
			delete particle;
			particle = new particle::Water(x,y);
			break;
		case 9: //¾àÃÊ
			delete particle;
			particle = new particle::Heal(x,y);
			break;
		case 10: //¾¾»Ñ¸®±â
			delete particle;
			particle = new particle::Heal2(x,y);
			break;
		case 35://¸ÞÅ×¿À
			delete particle;
			particle = new particle::FireRain(x,y);
			break;
		case 100: //¸÷ °ø°Ý 1¹ø?
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