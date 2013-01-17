#ifndef __menuscreen__
#define __menuscreen__ 

#include <iostream>
#include "gameScreen.h"
#include <SFML/Graphics.hpp>

class MenuScreen: public GameScreen{

	public:
		MenuScreen();
		~MenuScreen(){}

		void loadContent();
		void unloadContent();
		void update();
		void draw(sf::RenderWindow &window);

	private:
		sf::Text text;
		sf::Font font;

};
#endif