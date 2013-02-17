#ifndef __tileselector__
#define __tileselector__

#include <SFML/Graphics.hpp>

#include "tileset.h"
#include "global.h"

class TileSelector{
	private:	
		TileSet tileset;
		sf::Sprite selectedSprite;
		sf::Texture tmpTexture;
		std::vector< sf::IntRect > tiles;
		sf::IntRect tmpRect;
		sf::IntRect textureArea;
		unsigned int i;
	public:
		TileSelector(){};
		~TileSelector(){}
		void initialize(int num);
		void select(int x, int y);
		sf::IntRect getSelectedTile();
		void draw(sf::RenderWindow &window);
};

#endif