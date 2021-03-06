#include "entity.h"

Entity::Entity(const char *_path , sf::Vector2i _position) : currentDirection(Up), currentState(Staying){
	animation = new Animation();
	sprite.setPosition(_position.x, _position.y);

	animation->addTile(_path , 64, 64);
	animation->setSpeed(0.2f);
	animation->setTileRange(sf::Vector2i(2,1),8);

	margin.right = 0;
	margin.left = 0;
	margin.bottom = 0;
	margin.top = 0;
}

void Entity::move(sf::Vector2f _direction){
	sprite.move(_direction.x*SPEED*deltaTime.asSeconds(),_direction.y*SPEED*deltaTime.asSeconds());
}

void Entity::setCollisionBoxMargin(float top, float left, float bottom, float right){
	margin.left = left;
	margin.right = right;
	margin.top = top;
	margin.bottom = bottom;
}

bool Entity::isCollision(sf::Vector2f _direction, std::vector<sf::FloatRect> collideRects){
	collisionCheckSprite = sprite;
	collisionCheckSprite.move(_direction.x*SPEED*deltaTime.asSeconds(),_direction.y*SPEED*deltaTime.asSeconds());
	collisionBox.left = collisionCheckSprite.getGlobalBounds().left + margin.left;
	collisionBox.width = collisionCheckSprite.getGlobalBounds().width - margin.left - margin.right;
	collisionBox.top = collisionCheckSprite.getGlobalBounds().top + margin.top;
	collisionBox.height = collisionCheckSprite.getGlobalBounds().height - margin.top - margin.bottom;
	for(int i=0;i<collideRects.size();i++){
		if(collisionBox.intersects(collideRects[i]))
			return false;
	}
	return true;
}

void Entity::setDirection(int _direction){
	if(currentDirection != _direction){
		currentDirection = _direction;
		animation->setTileRange(sf::Vector2i(2,currentDirection+1),8);
	}
}

void Entity::setState(int _state){
	currentState = _state;
}

void Entity::update(std::vector<sf::FloatRect> collideRects){
	animation->update(&sprite, true);
	animation->playAnimation();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		animation->stopAnimationAt(1);
	}
	deltaTime = eTime.restart();
}

void Entity::draw(sf::RenderWindow &window){
	window.draw(sprite);
}

sf::Sprite Entity::getSprite(){
	return sprite;
}