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
	fire->setStartColor(252, 255, 0, 255);
	fire->setEndColor(255, 0, 0, 0);
}

void DragonSlave::update(){
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
		fire->fuelInSequence(0.3, 100);
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
	lightning->setColor(117, 231, 255);
	lightning->setThcikness(3);
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
	if (cloud->getLifeTime() < 0.6){
		lightning->draw(window);
	}

	cloud->draw(window);
}

Flood::Flood() : SkillEffect(){

	locationVarY = 280.0;

	flood = new ParticleSystem();
	flood->setTexture("img/particles/cloud.png");
	flood->setLocation(Vector2f(1300, 280));
	flood->setAngle(185);
	flood->setStartScale(0.6);
	flood->setStartScaleVar(1.0);
	flood->setStartColor(200, 200, 200, 30);
	flood->setEndColor(200, 200, 200, 30);
	flood->setLife(90);
	flood->setLifeVar(100);
	flood->setStartSpeed(4.4);
	flood->setStartSpeedVar(5.7);

}

void Flood::update(){

	flood->update();

	if (locationVarY < 720){
		flood->setLocationVar(Vector2f(1300, locationVarY));
		locationVarY += 6;
	}

	if (flood->getLifeTime() < 2.5){
		flood->fuel(50);
	}else if (flood->getNumberOfParticle() <= 0){
		SkillEffect::setEnd();
	}
}

void Flood::draw(RenderWindow &window){
	flood->draw(window);
}

Trident::Trident() : SkillEffect(){
	printf("sadf\n");
	water = new ParticleSystem();
	water->setTexture("img/particles/cloud.png");
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
	waterPillar->setStartColor(0, 0, 255, 0);
	waterPillar->setEndColor(0, 0, 255, 100);
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
	water->update();
	waterPillar->update();
	if (trident.getPosition().y < 1440){
		water->fuel(100);
		waterPillar->fuel(10);
	}

		waterPillar->setLocation(Vector2f(595, trident.getPosition().y - 50));
		waterPillar->setLocationVar(Vector2f(605, trident.getPosition().y + 150));
		trident.move(0, move);
		move += 0.5;

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
	tsunami->update();
	if (tsunami->getLifeTime() < 1.7){
		locationVarY += 2;
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

	seedTexture.loadFromFile("img/seed.png");
	seed.setTexture(seedTexture);
	seed.setScale(0.8, 0.8);
	seed.setPosition(540, 110);

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
	heal->update();

	if (alpha >= 0){
		seed.setColor(Color(255, 255, 255, alpha));
		alpha -= 9;
	}

	if (heal->getLifeTime() < 0.3)
		heal->fuel(80);
	else if (heal->getNumberOfParticle() <= 0){
		SkillEffect::setEnd();
	}
}

void Seed::draw(RenderWindow &window){
	heal->draw(window);
	window.draw(seed);
}

ElectricShock::ElectricShock() : SkillEffect(){

	timer = new ParticleSystem();

	lightning = new Lightning();
	lightning->setColor(117, 231, 255);
	lightning->setThcikness(3);
	lightning->setDetail(15);
	lightning->setDisplacement(300);
	lightning->setStartPosition(640, 0);
	lightning->setEndPosition(640, 360);

	randomizer = new Well512();
}

void ElectricShock::update(){
	timer->update();
	lightning->update();

		float randomX = randomizer->Next(590, 690);
		float randomY = randomizer->Next(150, 350);

		lightning->setStartPosition(randomX, randomY);

		randomX = randomizer->Next(590, 690);
		randomY = randomizer->Next(150, 350);

		lightning->setEndPosition(randomX, randomY);

		if (timer->getLifeTime() > 0.5)
			SkillEffect::setEnd();
}

void ElectricShock::draw(RenderWindow &window){

		lightning->draw(window);
}


LightningStorm::LightningStorm() : SkillEffect(){
	lightning = new Lightning();
	lightning->setColor(117, 231, 255);
	lightning->setThcikness(3);
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
	lightning->update();

	cloud->update();

	if (cloud->getLifeTime() < 0.6){
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
	snow->setEndColor(100, 100, 100, 0);
	snow->setAngle(260);
	snow->setRotation(190);
	snow->setLife(60);
	snow->setLifeVar(80);
	snow->setStartSpeed(3.5);
	snow->setStartSpeedVar(4.5);
	snow->setEndSpeed(3.5);
	snow->setEndSpeedVar(4.5);
}

void Blizzard::update(){

	cloud->update();
	snow->update();

	if (snow->getLifeTime() < 3.2){

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

	ice = new ParticleSystem();
	ice->setTexture("img/particles/cloud.png");
	ice->setLocation(Vector2f(540, 140));
	ice->setLocationVar(Vector2f(740, 340));
	ice->setStartScale(0.6);
	ice->setStartScaleVar(1.0);
	ice->setEndScale(0.3);
	ice->setEndScaleVar(0.4);
	ice->setAngle(84);
	ice->setLife(200);
	ice->setLifeVar(250);
	ice->setStartSpeed(0);
	ice->setStartSpeedVar(0);
	ice->setEndSpeed(0);
	ice->setEndSpeedVar(0);
	ice->setStartColor(117, 230, 255, 255);
	ice->setEndColor(117, 230, 255, 0);
}

void IceShield::update(){

	ice->update();
	if (ice->getLifeTime() < 0.5){
		ice->fuelInSequence(0.1, 10);
	}
	else{

		if (ice->getNumberOfParticle() <= 0){
			SkillEffect::setEnd();
		}
	}

}

void IceShield::draw(RenderWindow &window){
	ice->draw(window);
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
	spear.setPosition(-2500, 320);
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

	ice->update();
	spear.move(50, 0);
	if (spear.getPosition().x < 1290){
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
	particle->setStartScale(1.0);
	particle->setStartScaleVar(0.7);
	particle->setEndScale(0.1);
	particle->setEndScaleVar(0.0);
	particle->setAngle(90);
	particle->setLife(30);
	particle->setLifeVar(35);
	particle->setStartSpeed(4.4);
	particle->setStartSpeedVar(4.7);
	particle->setEndSpeed(0.0);
	particle->setEndSpeedVar(0.1);
	particle->setStartColor(58, 29, 1, 255);
	particle->setEndColor(154, 89, 31, 0);
}

void EarthSplitter::update(){

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
	sand->setRotation(190);
	sand->setLife(60);
	sand->setLifeVar(80);
	sand->setStartSpeed(3.5);
	sand->setStartSpeedVar(4.5);
	sand->setEndSpeed(3.5);
	sand->setEndSpeedVar(4.5);
}

void SandStorm::update(){

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
	particle->setLocation(Vector2f(-10, -10));
	particle->setLocationVar(Vector2f(1280, 0));
	particle->setStartScale(1.0);
	particle->setStartScaleVar(0.7);
	particle->setEndScale(0.1);
	particle->setEndScaleVar(0.0);
	particle->setAngle(270);
	particle->setLife(90);
	particle->setLifeVar(95);
	particle->setStartSpeed(0.4);
	particle->setStartSpeedVar(0.7);
	particle->setEndSpeed(10.4);
	particle->setEndSpeedVar(11.7);
	particle->setStartColor(58, 29, 1, 255);
	particle->setEndColor(154, 89, 31, 0);
}

void EarthShake::update(){

	particle->update();
	particle->fuelOnce(100);
	if (particle->getNumberOfParticle() <= 0){
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
	sand->setRotation(190);
	sand->setLife(60);
	sand->setLifeVar(80);
	sand->setStartSpeed(12.5);
	sand->setStartSpeedVar(12.5);
	sand->setEndSpeed(3.5);
	sand->setEndSpeedVar(4.5);
}

void Gust::update(){

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