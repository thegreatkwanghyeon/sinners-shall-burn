#include "particles.h"

using namespace particle;

FireBall::FireBall(int x, int y) : ParticleSystem(x, y){
	initialize(sf::Vector2i(-5,5));
	pos.x=x;
	pos.y=y;

	temp=pos;
	delta.restart();
}

void FireBall::initialize(sf::Vector2i _move){
	setTexture("img/particles/circle.png");
	setAngle(0);
	setAngleVar(90);
	setLife(90);
	setLifeVar(130);
	setSpeed(1);
	setSpeedVar(2);
	setStartColor(255, 0, 0, 255);
	setEndColor(255, 180, 0, 0);

	//여기부턴 이동할거면 쓸것
	move=_move;
}
void FireBall::setLocationList(){
	setLocation(sf::Vector2i(temp.x+100,temp.y-50));
	setLocationVar(sf::Vector2i(temp.x+150,temp.y));
	fuelInSequence(0.0, 10);
	setMove();
}
void FireBall::setMove(){
	if(delta.getElapsedTime().asSeconds() >= 0.01){
		delta.restart();
		temp.x+=move.x;
		temp.y+=move.y;
	}
}

Water::Water(int x, int y) : ParticleSystem(x, y){
	initialize(sf::Vector2i(0,-5));
	pos.x=x;
	pos.y=y;

	temp=pos;
	delta.restart();
}

void Water::initialize(sf::Vector2i _move){
	setTexture("img/particles/circle.png");
	setAngle(0);
	setAngleVar(360);
	setLife(150);
	setLifeVar(180);
	setSpeed(0.3);
	setSpeedVar(0.7);
	setStartColor(0, 0, 150, 100);
	setEndColor(0, 0, 255, 0);

	//여기부턴 이동할거면 쓸것
	move=_move;
}
void Water::setLocationList(){
	setLocation(sf::Vector2i(temp.x-25,temp.y));
	setLocationVar(sf::Vector2i(temp.x+25,temp.y+50));
	fuelInSequence(0.0, 10);

	setMove();
}
void Water::setMove(){
	if(delta.getElapsedTime().asSeconds() >= 0.01){
		delta.restart();
		temp.x-=move.x;
		temp.y+=move.y;
	}
}

Explosion::Explosion(int x, int y) : ParticleSystem(x, y){
	initialize();
	pos.x=x;
	pos.y=y;
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
	pos.x=x;
	pos.y=y;
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
	fireball[0] = new FireBall(300,0);
	fireball[1] = new FireBall(500,50);
	fireball[2] = new FireBall(1000,100);
	fireball[3] = new FireBall(200,150);
	fireball[4] = new FireBall(700,300);
	fireball[5] = new FireBall(400,350);
	fireball[6] = new FireBall(500,300);
	pos.x=x;
	pos.y=y;
}
void FireRain::update(){
	for(int i=0;i<7;i++){
		fireball[i]->update();
	}
}
void FireRain::draw(sf::RenderWindow &window){
	for(int i=0;i<7;i++){
		fireball[i]->draw(window);
	}
}
void FireRain::setLocationList(){
	for(int i=0;i<7;i++)
		fireball[i]->setLocationList();
}

Cut::Cut(int x, int y) : ParticleSystem(x, y){
	initialize(sf::Vector2i(-20,20));
	pos.x=x;
	pos.y=y;

	temp=pos;
	delta.restart();
}

void Cut::initialize(sf::Vector2i _move){
	setTexture("img/particles/scircle.png");
	setAngle(30);
	setAngleVar(60);
	setLife(50);
	setLifeVar(100);
	setSpeed(1);
	setSpeedVar(2);
	setStartColor(255, 0, 0, 255);
	setEndColor(255, 0, 0, 0);

	//여기부턴 이동할거면 쓸것
	move=_move;
}
void Cut::setLocationList(){
	setLocation(sf::Vector2i(temp.x+300,temp.y-150));
	setLocationVar(sf::Vector2i(temp.x+305,temp.y-145));
	fuelInSequence(0.0, 10);
	setMove();
}
void Cut::setMove(){
	if(delta.getElapsedTime().asSeconds() >= 0.01){
		delta.restart();
		temp.x+=move.x;
		temp.y+=move.y;
	}
}