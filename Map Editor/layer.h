#ifndef __layer__
#define __layer__

#include "global.h"
#include "tileselector.h"
#include "tileputter.h"

class Layer{
	private:
		TileSelector selector;
		TilePutter putter;
		FILE* saveMap;
		std::string saveName;
	public:
		Layer(std::string string);
		~Layer(){}
		void setTexture(int num);
		void update(sf::RenderWindow &window, sf::Event &event);
		void draw(sf::RenderWindow &window);
		void save();
};

#endif