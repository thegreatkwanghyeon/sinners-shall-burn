#ifndef __character__
#define __character__

#include <SFML/Graphics.hpp>
#include "animation.h"

class Character{
	private:
		sf::Sprite sprite;
		Animation *animation;		
		void Move();
	public:
		Character(float _x, float _y);
		~Character(){delete animation;}
		void update();
		void draw(sf::RenderWindow &window);
};
#endif