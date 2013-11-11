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
}

void FireBall::update(){
	
	if(fireballParticle->getSpeed() > 0.5){
		fireballParticle->update();
		fireballParticle->fuel(30);
		fireballParticle->setSpeed(fireballParticle->getSpeed() - 0.01);
		printf("update\n");
	}
}

void FireBall::draw(RenderWindow &window){
	fireballParticle->draw(window);
}