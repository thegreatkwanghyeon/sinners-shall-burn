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
	setSpeed(0.3);
	setSpeedVar(0.7);
	setStartColor(0, 0, 150, 100);
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
	setStartColor(0, 0, 200, 100);
	setEndColor(0, 0, 200, 0);
}