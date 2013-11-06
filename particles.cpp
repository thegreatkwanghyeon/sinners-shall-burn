#include "particles.h"

using namespace particle;

FireBall::FireBall(int _x, int _y) : ParticleSystem(x, y){
	initialize();
	x=_x;
	y=_y;
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
	setLocation(sf::Vector2i(x-100,y-100));
	setLocationVar(sf::Vector2i(x+100,y+100));
	fuelInSequence(0.0, 10);
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

FireRain::FireRain(int x, int y) : ParticleSystem(x, y){
	for(int i=0;i<10;i++){
		fireball[i] = new FireBall(i*50,i*50);
	}
}
void FireRain::update(){
	for(int i=0;i<10;i++){
		fireball[i]->update();
	}
}
void FireRain::draw(sf::RenderWindow &window){
	for(int i=0;i<10;i++){
		fireball[i]->draw(window);
	}
}
void FireRain::setLocationList(){
	for(int i=0;i<10;i++)
		fireball[i]->setLocationList();
}