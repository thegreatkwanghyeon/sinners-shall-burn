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
		void initialize(int num, int width, int height, int currentLayer);
		void setTexture(int num, int width, int height, int currentLayer);
		void update(sf::RenderWindow &window, sf::Event &event);
		void draw(sf::RenderWindow &window);
		void save();
};

#endif