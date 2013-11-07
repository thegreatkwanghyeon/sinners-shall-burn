#include "particlelist.h"

ParticleList::ParticleList(int _x, int _y){
	x=_x;
	y=_y;
	particle = new particle::FireBall(x,y);
}
void ParticleList::setParticle(int _num){
	num=_num;
	switch(num){
		case 1: //ȭ����
			delete particle;
			particle = new particle::FireBall(x,y);
			break;
		case 2: //Ÿ������ ȭ��
			delete particle;
			particle = new particle::Explosion(x,y);
			break;
		case 3://�ӽ� : ���� ��
			delete particle;
			particle = new particle::FireRain(x,y);
			break;
		case 5: //�����
			delete particle;
			particle = new particle::Rain(x,y);
			break;
		case 6: //ħ��
			delete particle;
			particle = new particle::Water(x,y);
			break;
		case 100: //�� ���� 1��?
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