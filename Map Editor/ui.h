#ifndef __ui__
#define __ui__

#include "stdafx.h"
#include "global.h"

class UI{
	private:
		sf::RectangleShape vLine, hLine;
	public:
		UI();
		~UI(){};
		void draw(sf::RenderWindow &window);
};

#endif