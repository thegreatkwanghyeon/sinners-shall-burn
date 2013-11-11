#include "particlelist.h"

using namespace skill;

ParticleList::ParticleList(int _x, int _y){
	x=_x;
	y=_y;
	skillEffect = new SkillEffect();
	sound.setLoop(false);
}
void ParticleList::setParticle(int _num, sf::String _path, bool isSound){
	num=_num;
	if(isSound){
		sound.resetBuffer();
		soundBuffer.loadFromFile(_path);
		sound.setBuffer(soundBuffer);
		sound.play();
	}
	switch(num){
		case 1: //È­¿°±¸
			{
			delete skillEffect;
			skillEffect = new FireBall();
			}

			break;
		case 2: //Å¸¿À¸£´Â È­¿°
			delete skillEffect;
			skillEffect = new FireBall();
			//particle = new particle::Beam(x,y);
			break;
		case 3://Áö¿ÁºÒ
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 4://¼¼¸êÈ­
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 5: //±â¿ìÁ¦
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 6: //Ä§¼ö
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 9: //¾àÃÊ
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 10: //¾¾»Ñ¸®±â
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 11: //Èí¼ö
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 19: //¾óÀ½¹æÆÐ
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 35://¸ÞÅ×¿À
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 50: //¸÷ °ø°Ý : ±¸¿ï?
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 51: //¸÷ °ø°Ý : ºí·¯µð¾ÆÀÌ(´«¿¡¼­ ºö!)
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		default : 
			delete skillEffect;
			skillEffect = new FireBall();
	}
}
ParticleList::~ParticleList(){
	delete skillEffect;
}
void ParticleList::update(){
	sound.setVolume(soundVolume);
	skillEffect->update();
}

void ParticleList::draw(sf::RenderWindow &window){
	skillEffect->draw(window);
}