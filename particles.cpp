#include "particles.h"

using namespace particle;

Water::Water(int x, int y) : ParticleSystem(x, y){
	initialize();
}

void Water::initialize(){
	setTexture("img/particles/circle.png");
	setAngle(0);
	setAngleVar(360);
	setLife(90);
	setLifeVar(130);
	setSpeed(0.4);
	setSpeedVar(0.6);
	setStartColor(0, 180, 255, 255);
	setEndColor(0, 0, 255, 0);
}


Fire::Fire(int x, int y) : ParticleSystem(x, y){
	initialize();
}

void Fire::initialize(){
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