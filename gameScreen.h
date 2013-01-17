#ifndef __gamescreen__
#define __gamescreen__

#include "SFML/Graphics.hpp"

class GameScreen{
	public:
		GameScreen();
		~GameScreen(){}

		virtual void loadContent();
		virtual void unloadContent();
		virtual void update();
		virtual void draw(sf::RenderWindow &window);

};

#endif