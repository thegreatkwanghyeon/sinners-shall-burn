#ifndef __screenManager__
#define __screenManager__

#include <iostream>
#include <cstdio>
#include "gameScreen.h"
#include "menuScreen.h"
#include "titleScreen.h"

#define ScreenWidth 800
#define ScreenHeight 600

class ScreenManager {
	public:
		~ScreenManager(){}
		static ScreenManager &getInstance();

		void initialize();
		void loadContent();
		void update();
		void draw(sf::RenderWindow &window);

		void setScreen(GameScreen *screen);

	private:
		ScreenManager();
		ScreenManager(ScreenManager const&);
		void operator=(ScreenManager const&);

		std::string _text;
};


#endif