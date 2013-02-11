#ifndef __ui__
#define __ui__

#include <SFML/Graphics.hpp>
#include "global.h"

class UI{
	private:
		sf::RectangleShape vLine;
	public:
		UI();
		~UI(){};
		void draw(sf::RenderWindow &window);
};

#endif