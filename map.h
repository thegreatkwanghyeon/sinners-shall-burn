#ifndef __map__
#define __map__

#include "stdafx.h"

class Map{

	private:

		sf::Sprite sprite;
		sf::Texture mapTexture;

	public:
		Map(std::string texturePath);
		~Map(){};
		void draw(sf::RenderWindow &window);
};

#endif