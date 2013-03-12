#include "player.h"


Player::Player(const char *_path , sf::Vector2i _position) : Entity(_path, _position){
	stats.LoadFile("xmls/text.xml");
	TiXmlElement *pElement = stats.FirstChildElement("Enemy");
	font.loadFromFile("font/spike.ttf");
	txtStats.setFont(font);
	txtStats.setString(MTW(pElement->GetText()));
	txtStats.setColor(sf::Color(0,0,0,255));
	txtStats.setPosition(350.0f,50.0f);
	Entity::setCollisionBoxMargin(40,20,10,20);
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
	window.draw(txtStats);
}