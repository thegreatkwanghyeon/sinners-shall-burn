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
		std::vector< TILE > mapSprites;
		TILE tmpSprite;
		sf::Texture tmpTexture;
		unsigned int i, j;
		sf::IntRect mapArea;
		bool able, contain;
		std::string saveTexture;
	public:
		TilePutter(){}
		~TilePutter(){}
		void initialize(std::string mainTexture);
		void putTile(int x, int y, sf::IntRect textureRect);
		void revert();
		void clear();
		void draw(sf::RenderWindow &window);
		std::vector< TILE > getMap();
};

#endif