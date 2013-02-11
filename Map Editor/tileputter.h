#ifndef __tileputter__
#define __tileputter__

#include <SFML/Graphics.hpp>
#include "global.h"

class TilePutter{
	private:
		std::vector< sf::IntRect > rects;
		std::vector< sf::IntRect > containRects;
		sf::IntRect tmpRect;
		sf::IntRect tmpContainRect;
		std::vector< sf::Sprite > mapSprites;
		sf::Sprite tmpSprite;
		sf::Texture tmpTexture;
		unsigned int i, j;
		sf::IntRect mapArea;
		bool able, contain;
	public:
		TilePutter(){}
		~TilePutter(){}
		void initialize(sf::Texture mainTexture);
		void putTile(int x, int y, sf::IntRect textureRect);
		void revert();
		void clear();
		void draw(sf::RenderWindow &window);
};

#endif