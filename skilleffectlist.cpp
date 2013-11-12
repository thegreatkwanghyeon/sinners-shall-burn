#include "skilleffectlist.h"

using namespace skill;

FireBall::FireBall() : SkillEffect(){
	Well512 randomizer;

	height = -4;
	scale = 1;
	fuel = 10;

	fireballParticle = new ParticleSystem();
	fireballParticle->setTexture("img/particles/fire.png");
	fireballParticle->setLocation(sf::Vector2f(610, 200));
	fireballParticle->setLocationVar(sf::Vector2f(630, 220));
	fireballParticle->setAngle(0);
	fireballParticle->setAngleVar(360);
	fireballParticle->setLife(5);
	fireballParticle->setLifeVar(6);
	fireballParticle->setSpeed(5);
	fireballParticle->setSpeedVar(5.5);
	fireballParticle->setStartColor(255, 0, 0, 255);
	fireballParticle->setStartColor(200, 10, 10, 255);
	fireballParticle->setEndColor(255, 30, 0, 0);
}

void FireBall::update(){
	
	if(scale > 0.7){
		fireballParticle->update();
		fireballParticle->fuel(fuel);

		if (fuel < 120){
			fuel += 4;
		}

		if (fireballParticle->getLifeTime() > 0.3){
			fireballParticle->setSpeed(fireballParticle->getSpeed() - 0.12);
			sf::Vector2f location = fireballParticle->getLocation();
			sf::Vector2f locationVar = fireballParticle->getLocationVar();
			fireballParticle->setLocation(sf::Vector2f(location.x, location.y + height));
			fireballParticle->setLocationVar(sf::Vector2f(locationVar.x, locationVar.y + height));
			fireballParticle->setScale(scale);
			scale -= 0.007;
			height += 0.25;
		}
	}
	else{
		fireballParticle->update();
		fireballParticle->setAngle(0);
		fireballParticle->setAngleVar(360);
		fireballParticle->setLife(80);
		fireballParticle->setLifeVar(110);
		fireballParticle->setSpeed(1);
		fireballParticle->setSpeedVar(1.4);
		fireballParticle->setStartColor(150, 0, 0, 255);
		fireballParticle->setStartColorVar(100, 0, 0, 255);
		fireballParticle->setEndColor(100, 100, 100, 0);
		fireballParticle->fuelOnce(150);

		if (fireballParticle->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}

	}
}

void FireBall::draw(RenderWindow &window){
		fireballParticle->draw(window);
}

Rain::Rain(){
	cloud = new ParticleSystem();
	cloud->setTexture("img/particles/fire.png");
	cloud->setLocation(Vector2f(0, -40));
	cloud->setLocationVar(Vector2f(1280, 90));
	cloud->setStartColor(100, 100, 100, 100);
	cloud->setEndColor(20, 20, 20, 0);
	cloud->setAngle(180);
	cloud->setLife(100);
	cloud->setLifeVar(130);
	cloud->setSpeed(0.2);
	cloud->setScaleVar(0.3);

	rain = new ParticleSystem();
	rain->setTexture("img/particles/rain.png");
	rain->setLocation(Vector2f(0, -40));
	rain->setLocationVar(Vector2f(1280, 0));
	rain->setStartColor(130, 130, 130, 100);
	rain->setEndColor(100, 100, 100, 0);
	rain->setAngle(260);
	rain->setRotation(190);
	rain->setLife(60);
	rain->setLifeVar(80);
	rain->setSpeed(3.5);
	rain->setSpeedVar(4.5);
}

void Rain::update(){
	if (rain->getLifeTime() < 3.2){
		cloud->update();
		rain->update();

		cloud->fuel(50);
		rain->fuel(50);
	}
	else{
		SkillEffect::setEnd();
	}
}

void Rain::draw(RenderWindow &window){
	rain->draw(window);
	cloud->draw(window);
}