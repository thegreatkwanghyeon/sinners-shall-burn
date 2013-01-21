#ifndef __character__
#define __character__

#include <SFML/Graphics.hpp>
#include "animation.h"

class Character{
	private:
		sf::Sprite sprite;
		void Move();
	public:
		Character(float _x, float _y);
		~Character(){}
		void update();
		void draw(sf::RenderWindow &window);
		sf::Sprite *pSprite;
		Animation animation;
};
#endif