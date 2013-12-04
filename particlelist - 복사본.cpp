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
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 2: //Å¸¿À¸£´Â È­¿°
			delete skillEffect;
			skillEffect = new DragonSlave();
			//particle = new particle::Beam(x,y);
			break;
		case 3://Áö¿ÁºÒ
			delete skillEffect;
			skillEffect = new HellFire();
			break;
		case 4://¼¼¸êÈ­
			delete skillEffect;
			skillEffect = new WorldFire();
			break;
		case 5: //Æø¿ì
			delete skillEffect;
			skillEffect = new Rain();
			break;
		case 6: //Ä§¼ö
			delete skillEffect;
			skillEffect = new Flood();
			break;
		case 7: //¾²³ª¹Ì
			delete skillEffect;
			skillEffect = new Flood();
			break;
		case 8: //»ïÁöÃ¢
			delete skillEffect;
			skillEffect = new Trident();
			break;
		case 9: //¾àÃÊ
			delete skillEffect;
			skillEffect = new Heal();
			break;
		case 10: //¾¾»Ñ¸®±â
			delete skillEffect;
			skillEffect = new Seed();
			break;
		case 11: //ÀÚ¿¬ÀÇ Èû
			delete skillEffect;
			skillEffect = new Heal();
			break;
		case 12: //»ý¸íÀÇ ¾¾¾Ñ
			delete skillEffect;
			skillEffect = new Heal();
			break;
		case 13 :
			delete skillEffect;
			skillEffect = new ElectricShock();
			break;
		case 14:
			delete skillEffect;
			skillEffect = new LightningBolt();
			break;
		case 15:
			delete skillEffect;
			skillEffect = new MagneticField ();
			break;
		case 16:
			delete skillEffect;
			skillEffect = new LightningStorm();
			break;
		case 17:
			delete skillEffect;
			skillEffect = new FrozenSpear();
			break;
		case 18:
			delete skillEffect;
			skillEffect = new Blizzard();
			break;
		case 19: //¾óÀ½¹æÆÐ
			delete skillEffect;
			skillEffect = new IceShield();
			break;
		case 20: 
			delete skillEffect;
			skillEffect = new AbsoluteZero();
			break;
		case 21:
			delete skillEffect;
			skillEffect = new EarthSplitter();
			break;
		case 22:
			delete skillEffect;
			skillEffect = new MuddyShield();
			break;
		case 23:
			delete skillEffect;
			skillEffect = new SandStorm();
			break;
		case 24:
			delete skillEffect;
			skillEffect = new EarthShake();
			break;
		case 25:
			delete skillEffect;
			skillEffect = new Gust();
			break;
		case 26:
			delete skillEffect;
			skillEffect = new SonicBoom();
			break;
		case 27:
			delete skillEffect;
			skillEffect = new Gust();
			break;
		case 28:
			delete skillEffect;
			skillEffect = new Vaccum();
			break;
		case 29:
			delete skillEffect;
			skillEffect = new Steam();
			break;
		case 30:
			delete skillEffect;
			skillEffect = new HotWater();
			break;
		case 31:
			delete skillEffect;
			skillEffect = new Frost();
			break;
		case 32:
			delete skillEffect;
			skillEffect = new Rain();
			break;
		case 33:
			delete skillEffect;
			skillEffect = new Hail();
			break;
		case 34:
			delete skillEffect;
			skillEffect = new Magma();
			break;
		case 35://¸ÞÅ×¿À
			delete skillEffect;
			skillEffect = new Meteor();
			break;
		case 36:
			delete skillEffect;
			skillEffect = new Poison();
			break;
		case 37:
			delete skillEffect;
			skillEffect = new FatalPoison();
			break;
		case 38:
			delete skillEffect;
			skillEffect = new Mud();
			break;
		case 39:
			delete skillEffect;
			skillEffect = new MuddyWater();
			break;
		case 40:
			delete skillEffect;
			skillEffect = new MuddyShield();
			break;
		case 41:
			delete skillEffect;
			skillEffect = new EarthShake();
			break;
		case 42:
			delete skillEffect;
			skillEffect = new Seed();
			break;
		case 43: //¸÷ °ø°Ý : ±¸¿ï?
			delete skillEffect;
			skillEffect = new SolarBeam();
			break;
		case 50: //¸÷ °ø°Ý : ±¸¿ï?
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 51: //¸÷ °ø°Ý : ºí·¯µð¾ÆÀÌ(´«¿¡¼­ ºö!)
			delete skillEffect;
			skillEffect = new FireBall();
			break;
		case 100 :
			delete skillEffect;
			skillEffect = new Miss();
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