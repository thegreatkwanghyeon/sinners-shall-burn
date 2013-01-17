#ifndef __character__
#define __character__

#include <SFML/Graphics.hpp>
#include "animation.h"

class Character{
	private:
		sf::Sprite sprite;

		float _x, _y;
	public:
		Character();
		~Character(){}

		sf::Sprite *pSprite;
		Animation  animation;

		void loadContent();
		void unloadContent();
		void update();
		void draw(sf::RenderWindow &window);

		void setPosition(float x, float y);
		
};
#endif