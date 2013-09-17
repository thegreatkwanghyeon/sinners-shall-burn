#include "particle.h"

Particle::Particle(sf::Texture texture, sf::Vector2f position, sf::Vector2f velocity, float angle, sf::Color color, int life){
	this->texture = texture;
	this->position = position;
	this->velocity = velocity;
	this->angle = angle;
	this->color = color;
	this->life = life;

	sprite.setColor(color);
	sprite.setPosition(position);
	sprite.setTexture(texture);

}

void Particle::setPosition(sf::Vector2f position){
	this->position = position;
	sprite.setPosition(position);
}

void Particle::setAngle(float angle){
	this->angle = angle;
}

void Particle::setColor(sf::Color color){
	this->color = color;
	sprite.setColor(color);
}

void Particle::setTexture(sf::Texture texture){
	this->texture = texture;
	sprite.setTexture(texture);
}

void Particle::setVelocity(sf::Vector2f velocity){
	this->velocity = velocity;
}

void Particle::setLife(int life){
	this->life = life; 
}

void Particle::draw(sf::RenderWindow &window){
	window.draw(sprite);
}