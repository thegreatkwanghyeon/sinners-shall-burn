#ifndef __character__
#define __character__

#define SPEED 200

#include <SFML/Graphics.hpp>
#include "animation.h"

class Character{
	private:
		sf::Sprite  sprite;
		Animation   *animation;		
		
		sf::Clock   eTime;
		sf::Time    deltaTime;

		void Move(sf::Time deltaTime);
	public:
		Character(float _x, float _y);
		~Character(){delete animation;}
		void update();
		void draw(sf::RenderWindow &window);
};
#endif