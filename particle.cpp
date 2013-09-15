#include "particle.h"

Particle::Particle(){
		life = 0;
		speed = 0;
		angle = 0;
		tmpElapsedTime = 0;
}

Particle::~Particle(){

}

void Particle::setTexture(sf::Texture texture){
	sf::Sprite::setTexture(texture);
}

void Particle::setAngle(int angle){
	this->angle = angle;
}

void Particle::setLife(int life){
	this->life = life;
}

float Particle::getLife(){
	return life;
}

void Particle::setSpeed(int speed){
	this->speed = speed;
}

void Particle::setSize(int size){
	this->size = size;
}

void Particle::move(float dt){
		radian = angle * M_PI/180;

		velocity.x = speed * cos(radian);
		velocity.y = -speed * sin(radian);

		this->setPosition(this->getPosition().x + velocity.x * dt, this->getPosition().y + velocity.y * dt);
}

void Particle::update(sf::Event &event){

	tmpElapsedTime += deltaTime.asSeconds();

	if(life > 0){
		move(deltaTime.asSeconds());
	}
	else{
		life = 0;
		speed = 0;
		angle = 0;
		tmpElapsedTime = 0;
	}

	if(tmpElapsedTime > 1){
		--life;
		tmpElapsedTime = 0;
	}

	deltaTime = eTime.restart();

}

void Particle::draw(sf::RenderWindow &window){
	window.draw(*this);
}