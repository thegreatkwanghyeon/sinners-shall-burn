#include "player.h"

Player::Player(const char *_path , sf::Vector2i _position) : Entity(_path, _position){
	stats.LoadFile("xmls/text.xml");
	TiXmlElement *pElement = stats.FirstChildElement("Enemy");
	font.loadFromFile("font/spike.ttf");
	txtStats.setFont(font);
	txtStats.setString(pElement->Attribute("hp"));
	txtStats.setColor(sf::Color(0,0,0,255));
	txtStats.setPosition(100.0f,100.0f);
}

void Player::update(){
	Entity::update();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		Entity::setDirection(Left);
		Entity::move(sf::Vector2i(-1,0));
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		Entity::setDirection(Right);
		Entity::move(sf::Vector2i(1,0));
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		Entity::setDirection(Up);
		Entity::move(sf::Vector2i(0,-1));
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		Entity::setDirection(Down);
		Entity::move(sf::Vector2i(0,1));
	}
}

void Player::draw(sf::RenderWindow &window){
	Entity::draw(window);
	window.draw(txtStats);
}