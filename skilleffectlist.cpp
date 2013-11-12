#include "skilleffectlist.h"

using namespace skill;

FireBall::FireBall() : SkillEffect(){

	explosionParticle = new ParticleSystem();
	explosionParticle->setTexture("img/particles/fire.png");
	explosionParticle->setLocation(Vector2f(490, 130));
	explosionParticle->setLocationVar(Vector2f(690, 330));
	explosionParticle->setAngle(0);
	explosionParticle->setAngleVar(360);
	explosionParticle->setLife(20);
	explosionParticle->setLifeVar(30);
	explosionParticle->setStartSpeed(0);
	explosionParticle->setStartSpeedVar(0);
	explosionParticle->setEndSpeed(0.3);
	explosionParticle->setEndSpeedVar(0.4);
	explosionParticle->setStartColor(252, 255, 0, 255);
	explosionParticle->setEndColor(255, 0, 0, 255);
}

void FireBall::update(){

	explosionParticle->update();
	explosionParticle->fuelOnce(100);

	if (explosionParticle->getNumberOfParticle() <= 0){
		SkillEffect::setEnd();
	}

}

void FireBall::draw(RenderWindow &window){
	explosionParticle->draw(window);
}

Rain::Rain() : SkillEffect(){
	cloud = new ParticleSystem();
	cloud->setTexture("img/particles/cloud.png");
	cloud->setLocation(Vector2f(0, -40));
	cloud->setLocationVar(Vector2f(1280, 90));
	cloud->setStartColor(100, 100, 100, 100);
	cloud->setEndColor(20, 20, 20, 0);
	cloud->setAngle(180);
	cloud->setLife(100);
	cloud->setLifeVar(130);
	cloud->setStartSpeed(0.2);
	cloud->setStartSpeedVar(0.3);
	cloud->setEndSpeed(0.2);
	cloud->setEndSpeedVar(0.3);

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
	rain->setStartSpeed(3.5);
	rain->setStartSpeedVar(4.5);
	rain->setEndSpeed(3.5);
	rain->setEndSpeedVar(4.5);
}

void Rain::update(){

	cloud->update();
	rain->update();

	if (rain->getLifeTime() < 3.2){

		cloud->fuel(50);
		rain->fuel(50);
	}
	else{
		if (cloud->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void Rain::draw(RenderWindow &window){
	rain->draw(window);
	cloud->draw(window);
}


HellFire::HellFire() : SkillEffect(){

	fuel = 5;
	locationVarX = 1280;

	fire = new ParticleSystem();
	fire->setTexture("img/particles/fire.png");
	fire->setLocation(Vector2f(0, 650));
	fire->setAngle(95);
	fire->setAngleVar(100);
	fire->setStartColor(252, 255, 0, 255);
	fire->setEndColor(255, 0, 0, 200);
	fire->setStartSpeed(1.3);
	fire->setStartSpeedVar(2.3);
	fire->setStartScale(1);
	fire->setStartScaleVar(0.8);
	fire->setEndScale(0.1);
	fire->setEndScaleVar(0.2);
	fire->setLife(45);
	fire->setLifeVar(55);

	smoke = new ParticleSystem();
	smoke->setTexture("img/particles/cloud.png");
	smoke->setLocation(Vector2f(0, 600));
	smoke->setAngle(90);
	smoke->setAngleVar(95);
	smoke->setStartColor(100, 100, 100, 100);
	smoke->setEndColor(0, 0, 0, 0);
	smoke->setStartSpeed(1.5);
	smoke->setStartSpeedVar(2.7);
	smoke->setStartScale(1);
	smoke->setStartScaleVar(0.8);
	smoke->setEndScale(0.3);
	smoke->setEndScaleVar(0.4);
	smoke->setLife(80);
	smoke->setLifeVar(90);

	lifeTime = 0;
}

void HellFire::update(){
	fire->update();
	smoke->update();

	if (locationVarX < 1480){
		locationVarX += 60;
		fire->setLocationVar(Vector2f(locationVarX, 720));
		smoke->setLocationVar(Vector2f(locationVarX, 600));
		lifeTime = fire->getLifeTime();
	}

	if (fire->getLifeTime() - lifeTime < 3.5){
		fire->fuel(100);
		smoke->fuel(50);
	}else if(fire->getNumberOfParticle() <= 0 && smoke->getNumberOfParticle() <= 0){
		SkillEffect::setEnd();
	}
}

void HellFire::draw(RenderWindow &window){
	smoke->draw(window);
	fire->draw(window);
}

LightningBolt::LightningBolt() : SkillEffect(){
	lightning = new Lightning();
	lightning->setColor(252, 255, 0);
	lightning->setThcikness(1);
	lightning->setDetail(3);
	lightning->setDisplacement(300);
	lightning->setStartPosition(640, 0);
	lightning->setEndPosition(640, 360);

	cloud = new ParticleSystem();
	cloud->setTexture("img/particles/cloud.png");
	cloud->setLocation(Vector2f(0, -40));
	cloud->setLocationVar(Vector2f(1280, 90));
	cloud->setStartColor(100, 100, 100, 100);
	cloud->setEndColor(20, 20, 20, 0);
	cloud->setAngle(180);
	cloud->setLife(100);
	cloud->setLifeVar(130);
	cloud->setStartSpeed(0.2);
	cloud->setStartSpeedVar(0.3);
	cloud->setEndSpeed(0.2);
	cloud->setEndSpeedVar(0.3);

	randomizer = new Well512();
}

void LightningBolt::update(){
	lightning->update();

	cloud->update();

	if (cloud->getLifeTime() < 0.6){
		float randomX = randomizer->Next(635, 645);

		lightning->setStartPosition(randomX, 0);
		lightning->setEndPosition(randomX, 720);

		cloud->fuel(50);
	}
	else{
		if (cloud->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void LightningBolt::draw(RenderWindow &window){
	if (cloud->getLifeTime() < 0.6)
	lightning->draw(window);

	cloud->draw(window);
}