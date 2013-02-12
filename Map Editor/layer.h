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
		std::string saveTexture;
		sf::Texture tmpTexture;
		std::string saveName;
	public:
		Layer(std::string string);
		~Layer(){}
		void setTexture(std::string mainTexture);
		void update(sf::RenderWindow &window);
		void draw(sf::RenderWindow &window);
		void save();
};

#endif