#include "skilleffectlist.h"

using namespace skill;

FireBall::FireBall() : SkillEffect(){

	fireParticle = new ParticleSystem();
	fireParticle->setTexture("img/particles/cloud.png");
	fireParticle->setLocation(Vector2f(565, 295));
	fireParticle->setLocationVar(Vector2f(655, 345));
	fireParticle->setStartScale(0.6);
	fireParticle->setStartScaleVar(1.0);
	fireParticle->setEndScale(0.3);
	fireParticle->setEndScaleVar(0.4);
	fireParticle->setAngle(84);
	fireParticle->setLife(40);
	fireParticle->setLifeVar(45);
	fireParticle->setStartSpeed(1.0);
	fireParticle->setStartSpeedVar(1.3);
	fireParticle->setStartColor(252, 255, 0, 255);
	fireParticle->setEndColor(255, 0, 0, 0);
}

void FireBall::update(){
	SkillEffect::update();
	fireParticle->update();
	if (fireParticle->getLifeTime() < 0.4){
		fireParticle->fuel(30);
	}
	else{

		if (fireParticle->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}

}

void FireBall::draw(RenderWindow &window){
	fireParticle->draw(window);
}

DragonSlave::DragonSlave() : SkillEffect(){

	fire = new ParticleSystem();
	fire->setTexture("img/particles/cloud.png");
	fire->setLocation(Vector2f(625, 800));
	fire->setLocationVar(Vector2f(650, 800));
	fire->setStartScale(0.0);
	fire->setStartScaleVar(0.2);
	fire->setEndScale(1.0);
	fire->setEndScaleVar(1.3);
	fire->setAngle(75);
	fire->setAngleVar(110);
	fire->setLife(60);
	fire->setLifeVar(80);
	fire->setStartSpeed(3.5);
	fire->setStartSpeedVar(4.5);
	fire->setEndSpeed(0.2);
	fire->setEndSpeedVar(0.5);
	fire->setStartColor(252, 255, 0, 255);
	fire->setEndColor(255, 0, 0, 0);
}

void DragonSlave::update(){
	SkillEffect::update();
	fire->update();
	if (fire->getLifeTime() < 0.4)
		fire->fuel(30);
	else{
		if (fire->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void DragonSlave::draw(RenderWindow &window){
	fire->draw(window);
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
	rain->setLife(60);
	rain->setLifeVar(80);
	rain->setStartSpeed(3.5);
	rain->setStartSpeedVar(4.5);
	rain->setEndSpeed(3.5);
	rain->setEndSpeedVar(4.5);
}

void Rain::update(){
	SkillEffect::update();
	cloud->update();
	rain->update();

	if (rain->getLifeTime() < 2.0){

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
	fire->setTexture("img/particles/Fire.png");
	fire->setLocation(Vector2f(0, 650));
	fire->setAngle(95);
	fire->setAngleVar(100);
	fire->setStartColor(252, 255, 0, 255);
	fire->setEndColor(255, 0, 0, 255);
	fire->setStartSpeed(1.3);
	fire->setStartSpeedVar(1.7);
	fire->setStartScale(1);
	fire->setStartScaleVar(0.8);
	fire->setEndScale(0.1);
	fire->setEndScaleVar(0.2);
	fire->setLife(70);
	fire->setLifeVar(80);

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
	SkillEffect::update();
	fire->update();
	smoke->update();

	if (locationVarX < 1480){
		locationVarX += 60 * time;
		fire->setLocationVar(Vector2f(locationVarX, 720));
		smoke->setLocationVar(Vector2f(locationVarX, 600));
		lifeTime = fire->getLifeTime();
	}

	if (fire->getLifeTime() - lifeTime < 3.5){
		fire->fuelInSequence(0.2, 100);
		smoke->fuel(50);
	}else if(fire->getNumberOfParticle() <= 0 && smoke->getNumberOfParticle() <= 0){
		SkillEffect::setEnd();
	}
}

void HellFire::draw(RenderWindow &window){
	smoke->draw(window);
	fire->draw(window);
}

WorldFire::WorldFire() : SkillEffect(){

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
	fire->setStartSpeedVar(1.7);
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

void WorldFire::update(){
	SkillEffect::update();
	fire->update();
	smoke->update();

	if (locationVarX < 1480){
		locationVarX += 60 * time;
		fire->setLocationVar(Vector2f(locationVarX, 720));
		smoke->setLocationVar(Vector2f(locationVarX, 600));
		lifeTime = fire->getLifeTime();
	}

	if (fire->getLifeTime() - lifeTime < 2.5){
		fire->fuel(100);
		smoke->fuel(50);
	}
	else if (fire->getNumberOfParticle() <= 0 && smoke->getNumberOfParticle() <= 0){
		SkillEffect::setEnd();
	}
}

void WorldFire::draw(RenderWindow &window){
	smoke->draw(window);
	fire->draw(window);
}


LightningBolt::LightningBolt() : SkillEffect(){
	lightning = new Lightning();
	lightning->setColor(248, 255, 50);
	lightning->setThcikness(2);
	lightning->setDetail(15);
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
	SkillEffect::update();
	lightning->update();

	cloud->update();

	if (cloud->getLifeTime() < 0.4){
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
	if (cloud->getLifeTime() < 0.6){
		lightning->draw(window);
	}

	cloud->draw(window);
}

Flood::Flood() : SkillEffect(){
	SkillEffect::update();
	locationVarY = 720;

	flood = new ParticleSystem();
	flood->setTexture("img/particles/fire.png");
	flood->setLocation(Vector2f(1380, 720));
	flood->setAngle(185);
	flood->setStartScale(0.6);
	flood->setStartScaleVar(0.8);
	flood->setEndScale(0.1);
	flood->setEndScaleVar(0.2);
	flood->setStartColor(200, 200, 200, 50);
	flood->setEndColor(100, 100, 100, 0);
	flood->setLife(110);
	flood->setLifeVar(120);
	flood->setStartSpeed(5.4);
	flood->setStartSpeedVar(6.7);

	temp = -8;

}

void Flood::update(){
	flood->update();

	if (locationVarY > 150){
		flood->setLocationVar(Vector2f(1380, locationVarY));
		locationVarY += temp * time;
	}
	else{
		temp = 8;
		flood->setLocationVar(Vector2f(1380, locationVarY));
		locationVarY += temp * time;
	}

	if (flood->getLifeTime() < 2.5){
		flood->fuel(80);
	}
	else if (flood->getNumberOfParticle() <= 0){
		SkillEffect::setEnd();
	}
}

void Flood::draw(RenderWindow &window){
	flood->draw(window);
}

Trident::Trident() : SkillEffect(){
	printf("sadf\n");
	water = new ParticleSystem();
	water->setTexture("img/particles/fire.png");
	water->setLocation(Vector2f(0, 720));
	water->setLocationVar(Vector2f(1280, 520));
	water->setAngle(90);
	water->setStartScale(1);
	water->setStartScaleVar(1);
	water->setEndScale(0.3);
	water->setEndScaleVar(0.4);
	water->setStartColor(0, 0, 255, 100);
	water->setEndColor(0, 0, 255, 0);
	water->setLife(30);
	water->setLifeVar(40);
	water->setStartSpeed(1.0);
	water->setStartSpeedVar(1.4);

	waterPillar = new ParticleSystem();
	waterPillar->setTexture("img/particles/cloud.png");
	waterPillar->setLocation(Vector2f(600, 720));
	waterPillar->setLocationVar(Vector2f(600, 520));
	waterPillar->setAngle(250);
	waterPillar->setAngleVar(290);
	waterPillar->setStartScale(1);
	waterPillar->setStartScaleVar(1);
	waterPillar->setEndScale(0.3);
	waterPillar->setEndScaleVar(0.4);
	waterPillar->setStartColor(0, 0, 255, 100);
	waterPillar->setEndColor(0, 0, 255, 200);
	waterPillar->setLife(30);
	waterPillar->setLifeVar(40);
	waterPillar->setStartSpeed(2.3);
	waterPillar->setStartSpeedVar(3.4);

	tridentTexture.loadFromFile("img/trident.png");
	trident.setTexture(tridentTexture);
	trident.setPosition(560, 720);

	move = -25;
}

void Trident::update(){
	SkillEffect::update();
	water->update();
	waterPillar->update();
	if (trident.getPosition().y < 980){
		water->fuel(100);
	}

	if (move < 10){
		waterPillar->fuel(22);
	}

	if (move < 0){
		waterPillar->setLocation(Vector2f(535, trident.getPosition().y + 50 * time));
		waterPillar->setLocationVar(Vector2f(665, trident.getPosition().y + 150 * time));
	}
		trident.move(0, move);
		move += 0.5 * time;

		if (water->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}

}

void Trident::draw(RenderWindow &window){
	water->draw(window);
	waterPillar->draw(window);
	window.draw(trident);

}

Tsunami::Tsunami() : SkillEffect(){

	locationVarY = 380;

	tsunami = new ParticleSystem();
	tsunami->setTexture("img/particles/cloud.png");
	tsunami->setLocation(Vector2f(-40, locationVarY));
	tsunami->setStartColor(0, 0, 255, 255);
	tsunami->setEndColor(0, 0, 255, 255);
	tsunami->setStartScale(1.0);
	tsunami->setStartScaleVar(1.3);
	tsunami->setEndScale(0.1);
	tsunami->setEndScaleVar(0.2);
	tsunami->setLife(100);
	tsunami->setLifeVar(130);
	tsunami->setStartSpeed(4.3);
	tsunami->setStartSpeedVar(4.7);
	tsunami->setAngle(0);
	tsunami->setAngleVar(10);
}

void Tsunami::update(){
	SkillEffect::update();
	tsunami->update();
	if (tsunami->getLifeTime() < 1.7){
		locationVarY += 2 * time;
		tsunami->setLocation(Vector2f(-40, locationVarY));
		tsunami->setLocationVar(Vector2f(-10, 720));
		tsunami->fuel(100);
	}
}

void Tsunami::draw(RenderWindow &window){
	tsunami->draw(window);
}

Heal::Heal() : SkillEffect(){
	heal = new ParticleSystem();
	heal->setTexture("img/particles/cloud.png");
	heal->setLocation(Vector2f(-30, 660));
	heal->setLocationVar(Vector2f(150, 700));
	heal->setStartColor(0, 255, 0, 255);
	heal->setEndColor(0, 255, 0, 0);
	heal->setStartScale(0.2);
	heal->setStartScaleVar(0.4);
	heal->setEndScale(0.0);
	heal->setEndScaleVar(0.1);
	heal->setLife(60);
	heal->setLifeVar(70);
	heal->setStartSpeed(0.8);
	heal->setStartSpeedVar(1.1);
	heal->setAngle(90);
}

void Heal::update(){
	SkillEffect::update();
	heal->update();
	if (heal->getLifeTime() < 0.7)
		heal->fuel(20);
	else if (heal->getNumberOfParticle() <= 0){
		SkillEffect::setEnd();
	}
}

void Heal::draw(RenderWindow &window){
	heal->draw(window);
}

Seed::Seed(){

	heal = new ParticleSystem();
	heal->setTexture("img/particles/cloud.png");
	heal->setLocation(Vector2f(0, 640));
	heal->setLocationVar(Vector2f(1280, 720));
	heal->setStartColor(0, 255, 0, 255);
	heal->setEndColor(0, 255, 0, 0);
	heal->setStartScale(0.2);
	heal->setStartScaleVar(0.4);
	heal->setEndScale(0.0);
	heal->setEndScaleVar(0.1);
	heal->setLife(160);
	heal->setLifeVar(170);
	heal->setStartSpeed(3.1);
	heal->setStartSpeedVar(3.7);
	heal->setAngle(90);

	alpha = 255;
}

void Seed::update(){
	SkillEffect::update();
	heal->update();

	if (heal->getLifeTime() < 0.6)
		heal->fuel(80);
	else if (heal->getNumberOfParticle() <= 0){
		SkillEffect::setEnd();
	}
}

void Seed::draw(RenderWindow &window){
	heal->draw(window);
}

ElectricShock::ElectricShock() : SkillEffect(){

	timer = new ParticleSystem();

	lightning = new Lightning();
	lightning->setColor(248, 255, 50);
	lightning->setThcikness(2);
	lightning->setDetail(15);
	lightning->setDisplacement(300);
	lightning->setStartPosition(640, 0);
	lightning->setEndPosition(640, 360);

	randomizer = new Well512();
}

void ElectricShock::update(){
	SkillEffect::update();
	timer->update();
	lightning->update();

		float randomX = randomizer->Next(590, 690);
		float randomY = randomizer->Next(150, 350);

		lightning->setStartPosition(randomX, randomY);

		randomX = randomizer->Next(590, 690);
		randomY = randomizer->Next(150, 350);

		lightning->setEndPosition(randomX, randomY);

		if (timer->getLifeTime() > 0.7)
			SkillEffect::setEnd();
}

void ElectricShock::draw(RenderWindow &window){

		lightning->draw(window);
}


LightningStorm::LightningStorm() : SkillEffect(){
	lightning = new Lightning();
	lightning->setColor(253, 255, 50);
	lightning->setThcikness(2);
	lightning->setDetail(15);
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

void LightningStorm::update(){
	SkillEffect::update();
	lightning->update();

	cloud->update();

	if (cloud->getLifeTime() < 1.3){
		float randomX = randomizer->Next(0, 1280);

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

void LightningStorm::draw(RenderWindow &window){
	if (cloud->getLifeTime() < 0.6){
		lightning->draw(window);
	}

	cloud->draw(window);
}

Blizzard::Blizzard() : SkillEffect(){
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

	snow = new ParticleSystem();
	snow->setTexture("img/particles/fire.png");
	snow->setLocation(Vector2f(0, -40));
	snow->setLocationVar(Vector2f(1380, 0));
	snow->setStartColor(130, 130, 130, 100);
	snow->setEndColor(100, 100, 100, 100);
	snow->setAngle(260);
	snow->setLife(70);
	snow->setLifeVar(85);
	snow->setStartSpeed(3.5);
	snow->setStartSpeedVar(4.5);
	snow->setEndSpeed(0.5);
	snow->setEndSpeedVar(1.5);
	snow->setStartScale(0.6);
	snow->setStartScaleVar(0.7);
	snow->setEndScale(0.2);
	snow->setEndScaleVar(0.3);
}

void Blizzard::update(){
	SkillEffect::update();
	cloud->update();
	snow->update();

	if (snow->getLifeTime() < 1.7){

		cloud->fuel(50);
		snow->fuel(10);
	}
	else{
		if (cloud->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void Blizzard::draw(RenderWindow &window){
	snow->draw(window);
	cloud->draw(window);
}


IceShield::IceShield() : SkillEffect(){
	particleLeft = new ParticleSystem();
	particleLeft->setTexture("img/particles/cloud.png");
	particleLeft->setLocation(Vector2f(440, 100));
	particleLeft->setLocationVar(Vector2f(440, 420));
	particleLeft->setStartColor(38, 252, 255, 255);
	particleLeft->setEndColor(255, 255, 255, 255);
	particleLeft->setAngle(0);
	particleLeft->setStartScale(1.0);
	particleLeft->setStartScaleVar(0.8);
	particleLeft->setEndScale(0.1);
	particleLeft->setEndScaleVar(0.2);
	particleLeft->setLife(15);
	particleLeft->setLifeVar(20);
	particleLeft->setStartSpeed(1.5);
	particleLeft->setStartSpeedVar(2.5);
	particleLeft->setEndSpeed(2.5);
	particleLeft->setEndSpeedVar(3.5);
	particleRight = new ParticleSystem();
	particleRight->setTexture("img/particles/cloud.png");
	particleRight->setLocation(Vector2f(790, 100));
	particleRight->setLocationVar(Vector2f(790, 420));
	particleRight->setStartColor(38, 252, 255, 255);
	particleRight->setEndColor(255, 255, 255, 255);
	particleRight->setAngle(180);
	particleRight->setStartScale(1.0);
	particleRight->setStartScaleVar(0.8);
	particleRight->setEndScale(0.1);
	particleRight->setEndScaleVar(0.2);
	particleRight->setLife(15);
	particleRight->setLifeVar(20);
	particleRight->setStartSpeed(1.5);
	particleRight->setStartSpeedVar(2.5);
	particleRight->setEndSpeed(2.5);
	particleRight->setEndSpeedVar(3.5);
}

void IceShield::update(){
	SkillEffect::update();
	particleLeft->update();
	particleRight->update();
	if (particleLeft->getLifeTime() < 0.4){
		particleLeft->fuel(50);
		particleRight->fuel(50);
	}
	else{
		if (particleLeft->getNumberOfParticle() <= 0)
			SkillEffect::setEnd();
	}
}

void IceShield::draw(RenderWindow &window){
	particleLeft->draw(window);
	particleRight->draw(window);
}

AbsoluteZero::AbsoluteZero() : SkillEffect(){

	ice = new ParticleSystem();
	ice->setTexture("img/particles/cloud.png");
	ice->setLocation(Vector2f(-10, -50));
	ice->setLocationVar(Vector2f(1280, 50));
	ice->setStartScale(0.6);
	ice->setStartScaleVar(1.0);
	ice->setEndScale(0.3);
	ice->setEndScaleVar(0.4);
	ice->setAngle(270);
	ice->setLife(150);
	ice->setLifeVar(170);
	ice->setStartSpeed(1.4);
	ice->setStartSpeedVar(1.7);
	ice->setEndSpeed(0.0);
	ice->setEndSpeedVar(0.1);
	ice->setStartColor(100, 100, 100, 100);
	ice->setEndColor(20, 20, 20, 0);
}

void AbsoluteZero::update(){
	SkillEffect::update();
	ice->update();
	if (ice->getLifeTime() < 1.7){
		ice->fuel(30);
	}
	else{

		if (ice->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}

}

void AbsoluteZero::draw(RenderWindow &window){
	ice->draw(window);
}

FrozenSpear::FrozenSpear() : SkillEffect(){

	texture.loadFromFile("img/frozenspear.png");
	spear.setTexture(texture);
	spear.setPosition(-2500, 290);
	ice = new ParticleSystem();
	ice->setTexture("img/particles/cloud.png");
	ice->setLocation(Vector2f(-10, -50));
	ice->setLocationVar(Vector2f(1280, 50));
	ice->setStartScale(0.6);
	ice->setStartScaleVar(1.0);
	ice->setEndScale(0.3);
	ice->setEndScaleVar(0.4);
	ice->setAngle(270);
	ice->setLife(150);
	ice->setLifeVar(170);
	ice->setStartSpeed(1.4);
	ice->setStartSpeedVar(1.7);
	ice->setEndSpeed(0.0);
	ice->setEndSpeedVar(0.1);
	ice->setStartColor(100, 100, 100, 100);
	ice->setEndColor(20, 20, 20, 0);
}

void FrozenSpear::update(){
	SkillEffect::update();
	ice->update();
	spear.move(50, 0);
	if (spear.getPosition().x < 1000){
		ice->fuel(80);
	}
	else{
		if (ice->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void FrozenSpear::draw(RenderWindow &window){
	window.draw(spear);
	ice->draw(window);
}


EarthSplitter::EarthSplitter() : SkillEffect(){

	particle = new ParticleSystem();
	particle->setTexture("img/particles/fire.png");
	particle->setLocation(Vector2f(-10, 920));
	particle->setLocationVar(Vector2f(1280, 720));
	particle->setStartScale(1.2);
	particle->setStartScaleVar(1.5);
	particle->setEndScale(0.1);
	particle->setEndScaleVar(0.0);
	particle->setAngle(90);
	particle->setLife(50);
	particle->setLifeVar(55);
	particle->setStartSpeed(4.4);
	particle->setStartSpeedVar(4.7);
	particle->setEndSpeed(0.0);
	particle->setEndSpeedVar(0.1);
	particle->setStartColor(58, 29, 1, 255);
	particle->setEndColor(154, 89, 31, 0);
}

void EarthSplitter::update(){
	SkillEffect::update();
	particle->update();
		particle->fuelOnce(100);
		if (particle->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}

}

void EarthSplitter::draw(RenderWindow &window){
	particle->draw(window);
}


SandStorm::SandStorm() : SkillEffect(){
	sand = new ParticleSystem();
	sand->setTexture("img/particles/cloud.png");
	sand->setLocation(Vector2f(-10, 520));
	sand->setLocationVar(Vector2f(1680, 720));
	sand->setStartColor(58, 29, 1, 125);
	sand->setEndColor(154, 89, 31, 0);
	sand->setAngle(150);
	sand->setLife(60);
	sand->setLifeVar(80);
	sand->setStartSpeed(3.5);
	sand->setStartSpeedVar(4.5);
	sand->setEndSpeed(3.5);
	sand->setEndSpeedVar(4.5);
}

void SandStorm::update(){
	SkillEffect::update();
	sand->update();

	if (sand->getLifeTime() < 1.3){
		sand->fuel(80);
	}
	else{
		if (sand->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void SandStorm::draw(RenderWindow &window){
	sand->draw(window);
}

EarthShake::EarthShake() : SkillEffect(){

	particle = new ParticleSystem();
	particle->setTexture("img/particles/fire.png");
	particle->setLocation(Vector2f(-10, -70));
	particle->setLocationVar(Vector2f(1280, 0));
	particle->setStartScale(1.0);
	particle->setStartScaleVar(1.7);
	particle->setEndScale(0.1);
	particle->setEndScaleVar(0.0);
	particle->setAngle(270);
	particle->setLife(40);
	particle->setLifeVar(55);
	particle->setStartSpeed(0.4);
	particle->setStartSpeedVar(0.7);
	particle->setEndSpeed(10.4);
	particle->setEndSpeedVar(11.7);
	particle->setStartColor(58, 29, 1, 255);
	particle->setEndColor(154, 89, 31, 0);
}

void EarthShake::update(){
	SkillEffect::update();
	particle->update();
	if (particle->getLifeTime() < 0.15)
		particle->fuel(15);
	else if (particle->getNumberOfParticle() <= 0){
		SkillEffect::setEnd();
	}

}

void EarthShake::draw(RenderWindow &window){
	particle->draw(window);
}


Gust::Gust() : SkillEffect(){
	sand = new ParticleSystem();
	sand->setTexture("img/particles/cloud.png");
	sand->setLocation(Vector2f(-100, 520));
	sand->setLocationVar(Vector2f(1880, 720));
	sand->setStartColor(200, 200, 200, 40);
	sand->setEndColor(10, 10, 10, 0);
	sand->setAngle(150);
	sand->setLife(60);
	sand->setLifeVar(80);
	sand->setStartSpeed(12.5);
	sand->setStartSpeedVar(12.5);
	sand->setEndSpeed(3.5);
	sand->setEndSpeedVar(4.5);
}

void Gust::update(){
	SkillEffect::update();
	sand->update();

	if (sand->getLifeTime() < 1.3){
		sand->fuel(80);
	}
	else{
		if (sand->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void Gust::draw(RenderWindow &window){
	sand->draw(window);
}


SonicBoom::SonicBoom() : SkillEffect(){
	sand = new ParticleSystem();
	sand->setTexture("img/particles/cloud.png");
	sand->setLocation(Vector2f(0, 360));
	sand->setLocationVar(Vector2f(50, 360));
	sand->setStartColor(200, 200, 200, 20);
	sand->setEndColor(10, 10, 10, 60);
	sand->setAngle(0);
	sand->setAngleVar(20);
	sand->setStartScale(0.4);
	sand->setStartScaleVar(0.7);
	sand->setEndScale(1.0);
	sand->setLife(30);
	sand->setLifeVar(40);
	sand->setStartSpeed(10.5);
	sand->setStartSpeedVar(14.5);
	sand->setEndSpeed(3.5);
	sand->setEndSpeedVar(4.5);
}

void SonicBoom::update(){
	SkillEffect::update();
	sand->update();

	if (sand->getLifeTime() < 0.20){
		sand->fuel(80);
	}
	else{
		if (sand->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void SonicBoom::draw(RenderWindow &window){
	sand->draw(window);
}

Steam::Steam() : SkillEffect(){
	sand = new ParticleSystem();
	sand->setTexture("img/particles/cloud.png");
	sand->setLocation(Vector2f(-200, 720));
	sand->setLocationVar(Vector2f(150, 570));
	sand->setStartColor(200, 200, 200, 100);
	sand->setEndColor(10, 10, 10, 0);
	sand->setAngle(25);
	sand->setAngleVar(35);
	sand->setStartScale(0.4);
	sand->setStartScaleVar(0.7);
	sand->setEndScale(1.0);
	sand->setLife(95);
	sand->setLifeVar(125);
	sand->setStartSpeed(3.5);
	sand->setStartSpeedVar(4.5);
	sand->setEndSpeed(1.3);
	sand->setEndSpeedVar(1.7);
}

void Steam::update(){
	SkillEffect::update();
	sand->update();

	if (sand->getLifeTime() < 1.4){
		sand->fuel(80);
	}
	else{
		if (sand->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void Steam::draw(RenderWindow &window){
	sand->draw(window);
}

HotWater::HotWater() : SkillEffect(){
	sand = new ParticleSystem();
	sand->setTexture("img/particles/cloud.png");
	sand->setLocation(Vector2f(390, -70));
	sand->setLocationVar(Vector2f(870, -40));
	sand->setStartColor(200, 200, 200, 100);
	sand->setEndColor(10, 10, 10, 0);
	sand->setAngle(270);
	sand->setStartScale(1.0);
	sand->setStartScaleVar(0.8);
	sand->setEndScale(0.1);
	sand->setEndScaleVar(0.2);
	sand->setLife(65);
	sand->setLifeVar(85);
	sand->setStartSpeed(1.5);
	sand->setStartSpeedVar(2.5);
	sand->setEndSpeed(3.5);
	sand->setEndSpeedVar(4.5);
}

void HotWater::update(){
	SkillEffect::update();
	sand->update();

	if (sand->getLifeTime() < 1.4){
		sand->fuel(30);
	}
	else{
		if (sand->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void HotWater::draw(RenderWindow &window){
	sand->draw(window);
}

StormyRain::StormyRain() : SkillEffect(){
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
	rain->setLife(60);
	rain->setLifeVar(80);
	rain->setStartSpeed(3.5);
	rain->setStartSpeedVar(4.5);
	rain->setEndSpeed(3.5);
	rain->setEndSpeedVar(4.5);

	storm = new ParticleSystem();
	storm->setTexture("img/particles/cloud.png");
	storm->setLocation(Vector2f(-10, 520));
	storm->setLocationVar(Vector2f(1680, 720));
	storm->setStartColor(220, 220, 220, 7);
	storm->setEndColor(240, 240, 240, 0);
	storm->setAngle(150);
	storm->setLife(130);
	storm->setLifeVar(150);
	storm->setStartSpeed(4.5);
	storm->setStartSpeedVar(5.5);
	storm->setEndSpeed(3.5);
	storm->setEndSpeedVar(4.5);

}

void StormyRain::update(){
	SkillEffect::update();
	cloud->update();
	rain->update();
	storm->update();

	if (rain->getLifeTime() < 3.2){

		cloud->fuel(50);
		rain->fuel(50);
		storm->fuel(80);
	}
	else{
		if (cloud->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void StormyRain::draw(RenderWindow &window){
	rain->draw(window);
	storm->draw(window);
	cloud->draw(window);
}


Hail::Hail() : SkillEffect(){
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
	rain->setTexture("img/particles/fire.png");
	rain->setLocation(Vector2f(0, -40));
	rain->setLocationVar(Vector2f(1280, 0));
	rain->setStartColor(130, 130, 130, 100);
	rain->setEndColor(100, 100, 100, 0);
	rain->setAngle(260);
	rain->setLife(60);
	rain->setLifeVar(80);
	rain->setStartSpeed(3.5);
	rain->setStartSpeedVar(4.5);
	rain->setEndSpeed(3.5);
	rain->setEndSpeedVar(4.5);
	rain->setStartScale(0.1);
	rain->setEndScale(0.1);
}

void Hail::update(){
	SkillEffect::update();
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

void Hail::draw(RenderWindow &window){
	rain->draw(window);
	cloud->draw(window);
}

Magma::Magma() : SkillEffect(){

	locationVarY = 720;

	flood = new ParticleSystem();
	flood->setTexture("img/particles/fire.png");
	flood->setLocation(Vector2f(1380, 720));
	flood->setAngle(185);
	flood->setStartScale(0.6);
	flood->setStartScaleVar(0.8);
	flood->setEndScale(0.1);
	flood->setEndScaleVar(0.2);
	flood->setStartColor(252, 255, 0, 255);
	flood->setEndColor(255, 0, 0, 255);
	flood->setLife(70);
	flood->setLifeVar(85);
	flood->setStartSpeed(5.4);
	flood->setStartSpeedVar(6.7);

	temp = -8;

}

void Magma::update(){
	SkillEffect::update();
	flood->update();

	if (locationVarY > 150){
		flood->setLocationVar(Vector2f(1380, locationVarY));
		locationVarY += temp * time;
	}
	else{
		temp = 8;
		flood->setLocationVar(Vector2f(1380, locationVarY));
		locationVarY += temp * time;
	}

	if (flood->getLifeTime() < 2.5){
		flood->fuel(80);
	}
	else if (flood->getNumberOfParticle() <= 0){
		SkillEffect::setEnd();
	}
}

void Magma::draw(RenderWindow &window){
	flood->draw(window);
}

Poison::Poison() : SkillEffect(){
	sand = new ParticleSystem();
	sand->setTexture("img/particles/cloud.png");
	sand->setLocation(Vector2f(390, -70));
	sand->setLocationVar(Vector2f(870, -40));
	sand->setStartColor(45, 140, 20, 255);
	sand->setEndColor(0, 255, 10, 0);
	sand->setAngle(270);
	sand->setStartScale(1.0);
	sand->setStartScaleVar(0.8);
	sand->setEndScale(0.1);
	sand->setEndScaleVar(0.2);
	sand->setLife(65);
	sand->setLifeVar(85);
	sand->setStartSpeed(1.5);
	sand->setStartSpeedVar(2.5);
	sand->setEndSpeed(3.5);
	sand->setEndSpeedVar(4.5);
}

void Poison::update(){
	SkillEffect::update();
	sand->update();

	if (sand->getLifeTime() < 0.3){
		sand->fuel(30);
	}
	else{
		if (sand->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void Poison::draw(RenderWindow &window){
	sand->draw(window);
}

FatalPoison::FatalPoison() : SkillEffect(){
	sand = new ParticleSystem();
	sand->setTexture("img/particles/cloud.png");
	sand->setLocation(Vector2f(390, -70));
	sand->setLocationVar(Vector2f(870, -40));
	sand->setStartColor(0, 255, 0, 100);
	sand->setEndColor(0, 255, 10, 0);
	sand->setAngle(270);
	sand->setStartScale(1.0);
	sand->setStartScaleVar(0.8);
	sand->setEndScale(0.1);
	sand->setEndScaleVar(0.2);
	sand->setLife(65);
	sand->setLifeVar(85);
	sand->setStartSpeed(1.5);
	sand->setStartSpeedVar(2.5);
	sand->setEndSpeed(3.5);
	sand->setEndSpeedVar(4.5);
}

void FatalPoison::update(){
	SkillEffect::update();
	sand->update();

	if (sand->getLifeTime() < 1.3){
		sand->fuel(30);
	}
	else{
		if (sand->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void FatalPoison::draw(RenderWindow &window){
	sand->draw(window);
}

Mud::Mud() : SkillEffect(){

	fire = new ParticleSystem();
	fire->setTexture("img/particles/cloud.png");
	fire->setLocation(Vector2f(640, 800));
	fire->setStartScale(0.0);
	fire->setStartScaleVar(0.2);
	fire->setEndScale(1.0);
	fire->setEndScaleVar(1.3);
	fire->setAngle(75);
	fire->setAngleVar(110);
	fire->setLife(60);
	fire->setLifeVar(80);
	fire->setStartSpeed(3.5);
	fire->setStartSpeedVar(4.5);
	fire->setEndSpeed(0.2);
	fire->setEndSpeedVar(0.5);
	fire->setStartColor(58, 29, 1, 255);
	fire->setEndColor(154, 89, 31, 2550);
}

void Mud::update(){
	SkillEffect::update();
	fire->update();
	if (fire->getLifeTime() < 0.3)
		fire->fuel(30);
	else{
		if (fire->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void Mud::draw(RenderWindow &window){
	fire->draw(window);
}


MuddyWater::MuddyWater() : SkillEffect(){
	sand = new ParticleSystem();
	sand->setTexture("img/particles/cloud.png");
	sand->setLocation(Vector2f(390, -70));
	sand->setLocationVar(Vector2f(870, -40));
	sand->setStartColor(58, 29, 1, 255);
	sand->setEndColor(154, 89, 31, 0);
	sand->setAngle(270);
	sand->setStartScale(1.0);
	sand->setStartScaleVar(0.8);
	sand->setEndScale(0.1);
	sand->setEndScaleVar(0.2);
	sand->setLife(65);
	sand->setLifeVar(85);
	sand->setStartSpeed(1.5);
	sand->setStartSpeedVar(2.5);
	sand->setEndSpeed(3.5);
	sand->setEndSpeedVar(4.5);
}

void MuddyWater::update(){
	SkillEffect::update();
	sand->update();

	if (sand->getLifeTime() < 0.7){
		sand->fuel(30);
	}
	else{
		if (sand->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void MuddyWater::draw(RenderWindow &window){
	sand->draw(window);
}

MuddyShield::MuddyShield() : SkillEffect(){
	particleLeft = new ParticleSystem();
	particleLeft->setTexture("img/particles/cloud.png");
	particleLeft->setLocation(Vector2f(440, 100));
	particleLeft->setLocationVar(Vector2f(440, 420));
	particleLeft->setStartColor(168, 119, 24, 255);
	particleLeft->setStartColor(168, 119, 24, 255);
	particleLeft->setAngle(0);
	particleLeft->setStartScale(1.0);
	particleLeft->setStartScaleVar(0.8);
	particleLeft->setEndScale(0.1);
	particleLeft->setEndScaleVar(0.2);
	particleLeft->setLife(15);
	particleLeft->setLifeVar(20);
	particleLeft->setStartSpeed(1.5);
	particleLeft->setStartSpeedVar(2.5);
	particleLeft->setEndSpeed(2.5);
	particleLeft->setEndSpeedVar(3.5);
	particleRight = new ParticleSystem();
	particleRight->setTexture("img/particles/cloud.png");
	particleRight->setLocation(Vector2f(790, 100));
	particleRight->setLocationVar(Vector2f(790, 420));
	particleRight->setStartColor(168, 119, 24, 255);
	particleRight->setStartColor(168, 119, 24, 255);
	particleRight->setAngle(180);
	particleRight->setStartScale(1.0);
	particleRight->setStartScaleVar(0.8);
	particleRight->setEndScale(0.1);
	particleRight->setEndScaleVar(0.2);
	particleRight->setLife(15);
	particleRight->setLifeVar(20);
	particleRight->setStartSpeed(1.5);
	particleRight->setStartSpeedVar(2.5);
	particleRight->setEndSpeed(2.5);
	particleRight->setEndSpeedVar(3.5);
}

void MuddyShield::update(){
	SkillEffect::update();
	particleLeft->update();
	particleRight->update();
	if (particleLeft->getLifeTime() < 0.4){
		particleLeft->fuel(50);
		particleRight->fuel(50);
	}
	else{
		if (particleLeft->getNumberOfParticle() <= 0)
			SkillEffect::setEnd();
	}
}

void MuddyShield::draw(RenderWindow &window){
	particleLeft->draw(window);
	particleRight->draw(window);
}

LandSlides::LandSlides() : SkillEffect(){
	snow = new ParticleSystem();
	snow->setTexture("img/particles/fire.png");
	snow->setLocation(Vector2f(0, -40));
	snow->setLocationVar(Vector2f(1380, 0));
	snow->setStartColor(58, 29, 1, 255);
	snow->setEndColor(154, 89, 31, 0);
	snow->setEndScale(0.1);
	snow->setEndScaleVar(0.2);
	snow->setAngle(270);
	snow->setLife(60);
	snow->setLifeVar(80);
	snow->setStartSpeed(3.5);
	snow->setStartSpeedVar(4.5);
	snow->setEndSpeed(3.5);
	snow->setEndSpeedVar(4.5);
}

void LandSlides::update(){
	SkillEffect::update();
	snow->update();

	if (snow->getLifeTime() < 1.2){
		snow->fuel(10);
	}
	else{
		if (snow->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void LandSlides::draw(RenderWindow &window){
	snow->draw(window);
}

SolarBeam::SolarBeam() : SkillEffect(){
	sand = new ParticleSystem();
	sand->setTexture("img/particles/cloud.png");
	sand->setLocation(Vector2f(590, -70));
	sand->setLocationVar(Vector2f(670, -40));
	sand->setStartColor(232, 255, 38, 100);
	sand->setEndColor(0, 0, 00, 0);
	sand->setAngle(270);
	sand->setStartScale(1.0);
	sand->setStartScaleVar(1.0);
	sand->setLife(95);
	sand->setLifeVar(125);
	sand->setStartSpeed(1.5);
	sand->setStartSpeedVar(2.5);
	sand->setEndSpeed(3.5);
	sand->setEndSpeedVar(4.5);
}

void SolarBeam::update(){
	SkillEffect::update();
	sand->update();

	if (sand->getLifeTime() < 1.3){
		sand->fuel(30);
	}
	else{
		if (sand->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void SolarBeam::draw(RenderWindow &window){
	sand->draw(window);
}

MagneticField::MagneticField(){
	particle = new ParticleSystem();
	particle->setTexture("img/particles/cloud.png");
	particle->setStartColor(120, 120, 120, 100);
	particle->setEndColor(30, 30, 30, 0);
	particle->setLocation(Vector2f(620, 250));
	particle->setAngle(0);
	particle->setAngleVar(360);
	particle->setLife(60);
	particle->setLifeVar(80);
	particle->setStartSpeed(1.4);
	particle->setStartSpeedVar(1.9);
	particle->setEndSpeed(0.1);
	particle->setEndSpeedVar(0.0);

}

void MagneticField::update(){
	SkillEffect::update();
	particle->update();
	if (particle->getLifeTime() < 2.3)
		particle->fuelInSequence(0.25, 80);
	else
		SkillEffect::setEnd();
}

void MagneticField::draw(RenderWindow &window){
	particle->draw(window);
}

ChainOfEarth::ChainOfEarth() : SkillEffect(){
	particleLeft = new ParticleSystem();
	particleLeft->setTexture("img/particles/cloud.png");
	particleLeft->setLocation(Vector2f(440, 100));
	particleLeft->setLocationVar(Vector2f(440, 420));
	particleLeft->setStartColor(58, 29, 1, 255);
	particleLeft->setEndColor(154, 89, 31, 255);
	particleLeft->setAngle(0);
	particleLeft->setStartScale(1.0);
	particleLeft->setStartScaleVar(0.8);
	particleLeft->setEndScale(0.1);
	particleLeft->setEndScaleVar(0.2);
	particleLeft->setLife(15);
	particleLeft->setLifeVar(20);
	particleLeft->setStartSpeed(1.5);
	particleLeft->setStartSpeedVar(2.5);
	particleLeft->setEndSpeed(2.5);
	particleLeft->setEndSpeedVar(3.5);
	particleRight = new ParticleSystem();
	particleRight->setTexture("img/particles/cloud.png");
	particleRight->setLocation(Vector2f(790, 100));
	particleRight->setLocationVar(Vector2f(790, 420));
	particleRight->setStartColor(58, 29, 1, 255);
	particleRight->setEndColor(154, 89, 31, 255);
	particleRight->setAngle(180);
	particleRight->setStartScale(1.0);
	particleRight->setStartScaleVar(0.8);
	particleRight->setEndScale(0.1);
	particleRight->setEndScaleVar(0.2);
	particleRight->setLife(15);
	particleRight->setLifeVar(20);
	particleRight->setStartSpeed(1.5);
	particleRight->setStartSpeedVar(2.5);
	particleRight->setEndSpeed(2.5);
	particleRight->setEndSpeedVar(3.5);
}

void ChainOfEarth::update(){
	SkillEffect::update();
	particleLeft->update();
	particleRight->update();
	if (particleLeft->getLifeTime() < 0.4){
		particleLeft->fuel(50);
		particleRight->fuel(50);
	}
	else{
		if (particleLeft->getNumberOfParticle() <= 0)
			SkillEffect::setEnd();
	}
}

void ChainOfEarth::draw(RenderWindow &window){
	particleLeft->draw(window);
	particleRight->draw(window);
}

Photosynthesis::Photosynthesis(){
	heal = new ParticleSystem();
	heal->setTexture("img/particles/cloud.png");
	heal->setLocation(Vector2f(0, 640));
	heal->setLocationVar(Vector2f(1280, 720));
	heal->setStartColor(0, 255, 0, 255);
	heal->setEndColor(0, 255, 0, 0);
	heal->setStartScale(0.2);
	heal->setStartScaleVar(0.4);
	heal->setEndScale(0.0);
	heal->setEndScaleVar(0.1);
	heal->setLife(160);
	heal->setLifeVar(170);
	heal->setStartSpeed(3.1);
	heal->setStartSpeedVar(3.7);
	heal->setAngle(90);

	alpha = 255;
}

void Photosynthesis::update(){
	SkillEffect::update();
	heal->update();

	if (alpha >= 0){
		alpha -= 9 * time;
	}

	if (heal->getLifeTime() < 0.5)
		heal->fuel(80);
	else if (heal->getNumberOfParticle() <= 0){
		SkillEffect::setEnd();
	}
}

void Photosynthesis::draw(RenderWindow &window){
	heal->draw(window);
}

Meteor::Meteor(){

	randomizer = new Well512();

	for (int i = 0; i < 5; i++){
		int rY = randomizer->Next(50, 300);
		int rX = randomizer->Next(500, 1780);
		meteor[i] = new ParticleSystem();
		meteor[i]->setTexture("img/particles/cloud.png");
		meteor[i]->setLocation(Vector2f(rX, -rY));
		meteor[i]->setLocationVar(Vector2f(rX + 180, -rY  + 50));
		meteor[i]->setStartScale(0.6);
		meteor[i]->setStartScaleVar(1.0);
		meteor[i]->setEndScale(0.3);
		meteor[i]->setEndScaleVar(0.4);
		meteor[i]->setAngle(60);
		meteor[i]->setLife(40);
		meteor[i]->setLifeVar(45);
		meteor[i]->setStartSpeed(1.0);
		meteor[i]->setStartSpeedVar(1.3);
		meteor[i]->setStartColor(252, 255, 0, 255);
		meteor[i]->setEndColor(255, 0, 0, 0);
	}
}

void Meteor::update(){
	SkillEffect::update();
	for (int i = 0; i < 5; i++){
		meteor[i]->update();
		meteor[i]->fuel(50);
		meteor[i]->setLocation(Vector2f(meteor[i]->getLocation().x - 32 * time, meteor[i]->getLocation().y + 20 * time));
		meteor[i]->setLocationVar(Vector2f(meteor[i]->getLocationVar().x - 32 * time, meteor[i]->getLocationVar().y + 20 * time));
	}
	if (meteor[0]->getLifeTime() > 1.7){
		SkillEffect::setEnd();
	}
}

void Meteor::draw(RenderWindow &window){
	for (int i = 0; i < 5; i++){
		meteor[i]->draw(window);
	}
}

Miss::Miss() : SkillEffect(){

	timer = new ParticleSystem();

	font.loadFromFile("font/aPinoL.ttf");

	miss.setString("MISS");
	miss.setFont(font);
	miss.setCharacterSize(100);
	miss.setPosition(540, 160);
	miss.setColor(Color::White);
}

void Miss::update(){
	SkillEffect::update();
	timer->update();
	if (timer->getLifeTime() > 0.3)
		SkillEffect::setEnd();
}

void Miss::draw(RenderWindow &window){
	window.draw(miss);
}

Frost::Frost() : SkillEffect(){
	sand = new ParticleSystem();
	sand->setTexture("img/particles/cloud.png");
	sand->setLocation(Vector2f(560, -70));
	sand->setLocationVar(Vector2f(670, -40));
	sand->setStartColor(147, 249, 255, 100);
	sand->setEndColor(0, 0, 0, 0);
	sand->setAngle(270);
	sand->setStartScale(1.0);
	sand->setStartScaleVar(1.0);
	sand->setLife(95);
	sand->setLifeVar(125);
	sand->setStartSpeed(1.5);
	sand->setStartSpeedVar(2.5);
	sand->setEndSpeed(3.5);
	sand->setEndSpeedVar(4.5);
}

void Frost::update(){
	SkillEffect::update();
	sand->update();

	if (sand->getLifeTime() < 1.3){
		sand->fuel(30);
	}
	else{
		if (sand->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}
}

void Frost::draw(RenderWindow &window){
	sand->draw(window);
}

Vaccum::Vaccum() : SkillEffect(){

	x = -400;
	y = -400;
	xv = 1780;
	yv = 1220;

	air = new ParticleSystem();
	air->setTexture("img/particles/cloud.png");
	air->setLocation(Vector2f(x, y));
	air->setLocationVar(Vector2f(xv, yv));
	air->setStartScale(0.6);
	air->setStartScaleVar(1.0);
	air->setEndScale(0.3);
	air->setEndScaleVar(0.4);
	air->setAngle(0);
	air->setAngle(360);
	air->setLife(50);
	air->setLifeVar(70);
	air->setStartSpeed(0.01);
	air->setStartSpeedVar(0.02);
	air->setEndSpeed(0.002);
	air->setEndSpeedVar(0.001);
	air->setStartColor(100, 100, 100, 100);
	air->setEndColor(20, 20, 20, 0);

}

void Vaccum::update(){
	SkillEffect::update();
	air->update();
	air->setLocation(Vector2f(x, y));
	air->setLocationVar(Vector2f(xv, yv));
	air->setStartColor(100, 100, 100, air->getStartColor().a - 1 * time);
	x += 22 * time;
	y += 15 * time;
	xv -= 22 * time;
	yv -= 15 * time;

	if (xv - x > 10){
		air->fuel(100);
	}
	else{
		if (air->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}


}

void Vaccum::draw(RenderWindow &window){
	air->draw(window);
}	