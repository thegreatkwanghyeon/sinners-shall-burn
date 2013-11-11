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
		case 1: //ȭ����
			{
			delete skillEffect;
			skillEffect = new FireBall();
			}

			break;
		case 2: //Ÿ������ ȭ��
			delete skillEffect;
			skillEffect = new FireBall();
			//particle = new particle::Beam(x,y);
			break;
		case 3://������
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 4://����ȭ
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 5: //�����
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 6: //ħ��
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 9: //����
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 10: //���Ѹ���
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 11: //���
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 19: //��������
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 35://���׿�
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 50: //�� ���� : ����?
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 51: //�� ���� : �������(������ ��!)
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