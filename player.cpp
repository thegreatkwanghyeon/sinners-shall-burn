#include "player.h"


Player::Player(const char *_path , sf::Vector2i _position) : Entity(_path, _position){
	stats.LoadFile("xmls/text.xml");
	TiXmlElement *pElement = stats.FirstChildElement("Enemy");
	font.loadFromFile("font/spike.ttf");
	txtStats.setFont(font);
	txtStats.setString(MTW(pElement->GetText()));
	txtStats.setColor(sf::Color(0,0,0,255));
	txtStats.setPosition(350.0f,50.0f);
}

void Player::update(std::vector<sf::FloatRect> collideRects){
	Entity::update(collideRects);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		Entity::setDirection(Left);
		Entity::move(sf::Vector2i(-1,0));
		for(unsigned int i=0;i<collideRects.size();i++){
			if(sprite.getGlobalBounds().intersects(collideRects[i]))
				sprite.setPosition(collideRects[i].left+collideRects[i].width, sprite.getPosition().y);
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		Entity::setDirection(Right);
		Entity::move(sf::Vector2i(1,0));
		for(unsigned int i=0;i<collideRects.size();i++){
			if(sprite.getGlobalBounds().intersects(collideRects[i]))
				sprite.setPosition(collideRects[i].left-sprite.getGlobalBounds().width, sprite.getPosition().y);
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		Entity::setDirection(Up);
		Entity::move(sf::Vector2i(0,-1));
		for(unsigned int i=0;i<collideRects.size();i++){
			if(sprite.getGlobalBounds().intersects(collideRects[i]))
				sprite.setPosition(sprite.getPosition().x, collideRects[i].top+collideRects[i].height);
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		Entity::setDirection(Down);
		Entity::move(sf::Vector2i(0,1));
		for(unsigned int i=0;i<collideRects.size();i++){
			if(sprite.getGlobalBounds().intersects(collideRects[i]))
				sprite.setPosition(sprite.getPosition().x, collideRects[i].top-sprite.getGlobalBounds().height);
		}
	}
}

void Player::draw(sf::RenderWindow &window){
	Entity::draw(window);
	window.draw(txtStats);
}