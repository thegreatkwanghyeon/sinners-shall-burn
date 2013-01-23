#include "character.h"

Character::Character(float _x, float _y){
	animation = new Animation();
	sprite.setPosition(_x, _y);
	animation->addTile("img/male_walkcycle.png",64, 64);
	animation->setSpeed(0.2);
	animation->setInterval(sf::Vector3i(5,3,2));
}

void Character::Move(sf::Time deltaTime){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		sprite.move(-SPEED*deltaTime.asSeconds(),0);
	}

	 if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		sprite.move(SPEED*deltaTime.asSeconds(),0);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		sprite.move(0,-SPEED*deltaTime.asSeconds());
	}

	 if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		sprite.move(0,SPEED*deltaTime.asSeconds());
	}
}

void Character::update(){
	animation->update(&sprite, true);
	Move(deltaTime);
	deltaTime = eTime.restart();
}

void Character::draw(sf::RenderWindow &window){
	window.draw(sprite);
}


