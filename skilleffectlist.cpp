#include "skilleffectlist.h"

using namespace skill;

FireBall::FireBall() : SkillEffect(){
	fireballParticle = new ParticleSystem();
	fireballParticle->setTexture("img/particles/circle.png");
	fireballParticle->setLocation(sf::Vector2i(640, 360));
	fireballParticle->setAngle(0);
	fireballParticle->setAngleVar(360);
	fireballParticle->setLife(4);
	fireballParticle->setLifeVar(7);
	fireballParticle->setSpeed(4);
	fireballParticle->setSpeedVar(7);
	fireballParticle->setStartColor(255, 0, 0, 255);
	fireballParticle->setEndColor(255, 180, 0, 0);

	explosionParticle = new ParticleSystem();
	explosionParticle->setTexture("img/particles/circle.png");
	explosionParticle->setLocation(sf::Vector2i(640, 360));
	explosionParticle->setAngle(0);
	explosionParticle->setAngleVar(360);
	explosionParticle->setLife(4);
	explosionParticle->setLifeVar(7);
	explosionParticle->setSpeed(4);
	explosionParticle->setSpeedVar(7);
	explosionParticle->setStartColor(255, 0, 0, 255);
	explosionParticle->setEndColor(50, 50, 50, 0);
}

void FireBall::update(){
	
	if(fireballParticle->getSpeed() > 0 && fireballParticle->getSpeedVar() > 0){
		fireballParticle->update();
		fireballParticle->fuel(50);
		fireballParticle->setSpeed(fireballParticle->getSpeed()-0.1);
		fireballParticle->setSpeedVar(fireballParticle->getSpeedVar()-0.1);
	}else{
		explosionParticle->update();
		explosionParticle->fuel(50);
		SkillEffect::setEnd();
	}
}

void FireBall::draw(RenderWindow &window){
	fireballParticle->draw(window);
	explosionParticle->draw(window);
}