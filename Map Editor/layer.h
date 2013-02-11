#ifndef __layer__
#define __layer__

#include "tileselector.h"
#include "tileputter.h"

class Layer{
	private:
		TileSelector selector;
		TilePutter putter;
	public:
		Layer(){}
		~Layer(){}
		void setTexture(sf::Texture mainTexture);
		void update(sf::RenderWindow &window);
		void draw(sf::RenderWindow &window);
};

#endif