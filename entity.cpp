#include "entity.h"

Entity::Entity(const char *_path , sf::Vector2i _position){
	animation = new Animation();
	sprite.setPosition(_position.x, _position.y);

	animation->addTile(_path , 64, 64);
	animation->setSpeed(0.2f);
	animation->setInterval(sf::Vector3i(5,3,2));
}

void Entity::move(sf::Vector2i _direction){
	sprite.move(_direction.x*SPEED*deltaTime.asSeconds(),_direction.y*SPEED*deltaTime.asSeconds());
}

void Entity::update(){
	animation->update(&sprite, true);
	deltaTime = eTime.restart();
}

void Entity::draw(sf::RenderWindow &window){
	window.draw(sprite);
}