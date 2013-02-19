#ifndef __ui__
#define __ui__

#include <SFML/Graphics.hpp>
#include "global.h"

class UI{
	private:
		sf::RectangleShape vLine, hLine;
		sf::Texture bottomTexture, rightTexture;
		sf::Sprite bottom, right;
	public:
		UI();
		~UI(){};
		void draw(sf::RenderWindow &window);
};

#endif