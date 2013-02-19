#ifndef __collide__
#define __collide__

#include <SFML/Graphics.hpp>
#include "global.h"

class Collide{
	private:

		struct CHECKER{
			sf::Sprite sprite;
			int num;
		};

		FILE* saveFile;
		unsigned int a;
		CHECKER tmpChecker;
		std::vector<CHECKER> checkers;
		sf::IntRect tmpRect;
		sf::IntRect mapArea;
		std::vector<sf::IntRect> rects;
		sf::Texture collide, no_collide;

	public:
		void initialize();
		void check(int x, int y);
		void draw(sf::RenderWindow &window);
		void save(std::string string);
};

#endif