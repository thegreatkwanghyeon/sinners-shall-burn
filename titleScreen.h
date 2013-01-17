#ifndef __titlescreen__
#define __titlescreen__ 

#include <iostream>
#include "gameScreen.h"
#include "character.h"
#include <SFML/Graphics.hpp>

class TitleScreen : public GameScreen{

	public:
		TitleScreen();
		~TitleScreen(){}

		void loadContent();
		void unloadContent();
		void update();
		void draw(sf::RenderWindow &window);

	private:
		sf::Text text;
		sf::Font font;

		Character character;

};
#endif