#include "skilleffectlist.h"

using namespace skill;

FireBall::FireBall() : SkillEffect(){
	Well512 randomizer;

	height = -4;
	scale = 1;

	fireballParticle = new ParticleSystem();
	fireballParticle->setTexture("img/particles/fire.png");
	fireballParticle->setLocation(sf::Vector2f(610, 200));
	fireballParticle->setLocationVar(sf::Vector2f(630, 220));
	fireballParticle->setAngle(0);
	fireballParticle->setAngleVar(360);
	fireballParticle->setLife(7);
	fireballParticle->setLifeVar(8);
	fireballParticle->setSpeed(6);
	fireballParticle->setSpeedVar(6.5);
	fireballParticle->setStartColor(255, 0, 0, 255);
	fireballParticle->setStartColor(200, 10, 10, 255);
	fireballParticle->setEndColor(255, 200, 0, 0);

	explosionParticle = new ParticleSystem();
	explosionParticle->setTexture("img/particles/fire.png");
	explosionParticle->setAngle(0);
	explosionParticle->setAngleVar(360);
	explosionParticle->setLife(80);
	explosionParticle->setLifeVar(110);
	explosionParticle->setSpeed(1);
	explosionParticle->setSpeedVar(1.4);
	explosionParticle->setStartColor(150, 0, 0, 255);
	explosionParticle->setStartColorVar(100, 0, 0, 255);
	explosionParticle->setEndColor(100, 100, 100, 0);
}

void FireBall::update(){
	
	if(scale > 0.7){
		fireballParticle->update();
		fireballParticle->fuel(120);
		fireballParticle->setSpeed(fireballParticle->getSpeed() - 0.12);
		sf::Vector2f location = fireballParticle->getLocation();
		sf::Vector2f locationVar = fireballParticle->getLocationVar();
		fireballParticle->setLocation(sf::Vector2f(location.x, location.y+height));
		fireballParticle->setLocationVar(sf::Vector2f(locationVar.x, locationVar.y + height));
		fireballParticle->setScale(scale);
		scale -= 0.007;
		height += 0.25;
	}
	else{
		explosionParticle->update();
		explosionParticle->setLocation(fireballParticle->getLocation());
		explosionParticle->setLocationVar(fireballParticle->getLocationVar());
		explosionParticle->fuelOnce(150);

		if (explosionParticle->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}

	}
}

void FireBall::draw(RenderWindow &window){

	if (scale > 0.7){
		fireballParticle->draw(window);
	}
	else{
		explosionParticle->draw(window);
	}
}