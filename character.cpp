#include "character.h"

Character::Character(float _x, float _y){
	sprite.setPosition(_x, _y);
	pSprite=&sprite;
	animation.addTile("img/number.jpg",100, 100);
	animation.setSpeed(100);

	//
	font.loadFromFile("font/font.ttf");
	text.setFont(font);
	
	text.setPosition(0.0f, 0.0f);
	text.setColor(sf::Color(100,100,100));
}

void Character::Move(sf::Time dt){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		sprite.move(-SPEED*dt.asSeconds(),0);
	}

	 if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		sprite.move(SPEED*dt.asSeconds(),0);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		sprite.move(0,-SPEED*dt.asSeconds());
	}

	 if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		sprite.move(0,SPEED*dt.asSeconds());
	}			
}

void Character::update(){

	sprintf(temp, "character.dt = %f", dt.asSeconds());
	text.setString(temp);

	//
	Move(dt);

	dt = eTime.restart();
}

void Character::draw(sf::RenderWindow &window){
	animation.update(pSprite, true);
	window.draw(sprite);

		window.draw(text);
}


