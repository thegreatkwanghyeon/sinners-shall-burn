#include "player.h"


Player::Player(const char *_path , sf::Vector2i _position) : Entity(_path, _position){
	Entity::setCollisionBoxMargin(40,20,10,20);

	skill = new Skill();

	for(int i=0;i<7;i++){//기본 원소
		element[i]=1;
		useElement[i]=i;
	}
	skill->setHave(1);
	skill->setHave(2);
	skill->setHave(3);
	skill->setHave(4);
	skill->setHave(5);
}

void Player::update(std::vector<sf::FloatRect> collideRects){
	Entity::update(collideRects);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		Entity::setDirection(Left);
		if(Entity::isCollision(sf::Vector2f(-1,0), collideRects))
			Entity::move(sf::Vector2f(-1,0));
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		Entity::setDirection(Right);
		if(Entity::isCollision(sf::Vector2f(1,0), collideRects))
			Entity::move(sf::Vector2f(1,0));
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		Entity::setDirection(Up);
		if(Entity::isCollision(sf::Vector2f(0,-1), collideRects))
			Entity::move(sf::Vector2f(0,-1));

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		Entity::setDirection(Down);
		if(Entity::isCollision(sf::Vector2f(0,1), collideRects))
			Entity::move(sf::Vector2f(0,1));
	}
}

void Player::draw(sf::RenderWindow &window){
	Entity::draw(window);
}