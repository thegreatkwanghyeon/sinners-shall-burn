#include "particles.h"

using namespace particle;

FireBall::FireBall(int x, int y) : ParticleSystem(x, y){
	initialize();
}

void FireBall::initialize(){
	setTexture("img/particles/circle.png");
	setAngle(85);
	setAngleVar(95);
	setLife(90);
	setLifeVar(130);
	setSpeed(0.4);
	setSpeedVar(0.6);
	setStartColor(255, 180, 0, 255);
	setEndColor(255, 0, 0, 0);
}
void FireBall::setLocationList(){
	setLocation(sf::Vector2i(540,250));
	setLocationVar(sf::Vector2i(540,280));
	fuelInSequence(0.0, 10);
	printf("shit");
}

Water::Water(int x, int y) : ParticleSystem(x, y){
	initialize();
}

void Water::initialize(){
	setTexture("img/particles/circle.png");
	setAngle(0);
	setAngleVar(360);
	setLife(90);
	setLifeVar(130);
	setSpeed(0.3);
	setSpeedVar(0.7);
	setStartColor(0, 0, 150, 100);
	setEndColor(0, 0, 255, 0);
}
void Water::setLocationList(){
	setLocation(sf::Vector2i(500,300));
	setLocationVar(sf::Vector2i(600,400));
	fuelInSequence(0.0, 10);
}

Explosion::Explosion(int x, int y) : ParticleSystem(x, y){
	initialize();
}

void Explosion::initialize(){
	setTexture("img/particles/circle.png");
	setAngle(70);
	setAngleVar(110);
	setLife(90);
	setLifeVar(130);
	setSpeed(0.4);
	setSpeedVar(0.6);
	setStartColor(255, 180, 0, 255);
	setEndColor(255, 0, 0, 0);
}
void Explosion::setLocationList(){
	setLocation(sf::Vector2i(0,0));
	setLocationVar(sf::Vector2i(1280,700));
	fuelInSequence(0.0, 10);
}
Rain::Rain(int x, int y) : ParticleSystem(x, y){
	initialize();
}

void Rain::initialize(){
	setTexture("img/particles/stick2.png");
	setAngle(220);
	setAngleVar(230);
	setLife(150);
	setLifeVar(200);
	setSpeed(3);
	setSpeedVar(4);
	setStartColor(0, 0, 255, 100);
	setEndColor(0, 0, 255, 0);
}
void Rain::setLocationList(){
	setLocation(sf::Vector2i(0,0));
	setLocationVar(sf::Vector2i(1280,700));
	fuelInSequence(0.0, 10);
}