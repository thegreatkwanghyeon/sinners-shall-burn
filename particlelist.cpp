#include "particlelist.h"

ParticleList::ParticleList(int _x, int _y){
	x=_x;
	y=_y;
	particle = new particle::FireBall(x,y);
	sound.setLoop(false);
}
void ParticleList::setParticle(int _num, sf::String _path, bool isSound){
	num=_num;
	if(isSound){
		sound.resetBuffer();
		soundBuffer.loadFromFile(_path);
		sound.setBuffer(soundBuffer);
		sound.play();
		path=_path;
	}
	switch(num){
		case 1: //È­¿°±¸
			delete particle;
			particle = new particle::FireBall(x,y);
			break;
		case 2: //Å¸¿À¸£´Â È­¿°
			delete particle;
			particle = new particle::Explosion(x,y);
			//particle = new particle::Beam(x,y);
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
		case 11: //Èí¼ö
			delete particle;
			particle = new particle::Drain(x,y);
			break;
		case 19: //¾óÀ½¹æÆÐ
			delete particle;
			particle = new particle::IceShield(x,y);
			break;
		case 35://¸ÞÅ×¿À
			delete particle;
			particle = new particle::FireRain(x,y);
			break;
		case 50: //¸÷ °ø°Ý : ±¸¿ï?
			delete particle;
			particle = new particle::Cut(x,y);
			break;
		case 51: //¸÷ °ø°Ý : ºí·¯µð¾ÆÀÌ(´«¿¡¼­ ºö!)
			delete particle;
			particle = new particle::Beam(x,y);
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
	sound.setVolume(soundVolume);
	particle->update();
}

void ParticleList::draw(sf::RenderWindow &window){
	particle->draw(window);
}
void ParticleList::setLocationList(){
	particle->setLocationList();
}