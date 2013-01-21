#ifndef __character__
#define __character__
#define SPEED 200

#include <cstdio>

#include <SFML/Graphics.hpp>
#include "animation.h"

class Character{
	private:
		sf::Sprite  sprite;
		
		sf::Clock   eTime;
		sf::Time    dt;
		
		sf::Font    font;
		sf::Text    text;
		
		char        temp[256];

		void Move(sf::Time dt);
	public:
		Character(float _x, float _y);
		~Character(){}
		void update();
		void draw(sf::RenderWindow &window);
		sf::Sprite *pSprite;
		Animation animation;
};
#endif