#include "player.h"

Player::Player(const char *_path , sf::Vector2i _position) : Entity(_path, _position){
}

void Player::update(){
	Entity::update();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		Entity::move(sf::Vector2i(-1,0));
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		Entity::move(sf::Vector2i(1,0));
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		Entity::move(sf::Vector2i(0,-1));
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		Entity::move(sf::Vector2i(0,1));
	}
}

void Player::draw(sf::RenderWindow &window){
	Entity::draw(window);
}