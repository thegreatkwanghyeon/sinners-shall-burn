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
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 2: //Ÿ������ ȭ��
			delete skillEffect;
			skillEffect = new DragonSlave();
			//particle = new particle::Beam(x,y);
			break;
		case 3://������
			delete skillEffect;
			skillEffect = new HellFire();
			break;
		case 4://����ȭ
			delete skillEffect;
			skillEffect = new WorldFire();
			break;
		case 5: //����
			delete skillEffect;
			skillEffect = new Rain();
			break;
		case 6: //ħ��
			delete skillEffect;
			skillEffect = new Flood();
			break;
		case 7: //������
			delete skillEffect;
			skillEffect = new Tsunami();
			break;
		case 8: //����â
			delete skillEffect;
			skillEffect = new Trident();
			break;
		case 9: //����
			delete skillEffect;
			skillEffect = new Seed();
			break;
		case 10: //���Ѹ���
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 14 :
			delete skillEffect;
			skillEffect = new LightningBolt();
			break;
		case 11: //����
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
		case 51: //�� ���� : ���������(������ ��!)
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