#ifndef __character__
#define __character__

#include <SFML/Graphics.hpp>
#include "animation.h"

class Character{
	private:
		sf::Sprite sprite;
	public:
		Character(float _x, float _y);
		~Character(){}
		void Draw(sf::RenderWindow &window);
		sf::Sprite *pSprite;
		Animation  animation;
};
#endif