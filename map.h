#ifndef __map__
#define __map__

#include "stdafx.h"
#include "tinyxml.h"
#include <SFML/Graphics.hpp>

class Map{

	private:

		TiXmlDocument mapTextureList;
		TiXmlNode * pNode;
		int num;

		sf::Sprite tmpSprite;
		sf::Texture tmpTexture;
		sf::IntRect tmpRect;
		std::string ground, object;

			float tmpData_posX, tmpData_posY;
			int tmpData_left, tmpData_width, tmpData_top, tmpData_height;
			int tmpData_textureNum;
			int tempData_colNum;

		char tmpString[100];
		char tmpChar[1];
		int groundTextureNum;
		int objectTextureNum;

		std::vector<sf::Sprite> groundSprites;
		std::vector<sf::Sprite> objectSprites;
		std::vector<sf::Texture> groundTextures;
		std::vector<sf::Texture> objectTextures;
		std::vector<sf::IntRect> collideRects;

		FILE* loadMap;
		std::string loadMapName;
		int loadSize;

	public:
		Map();
		~Map(){};
		void initialize();
		void load(const char* MAPNAME);
		void ground_Draw(sf::RenderWindow &window);
		void object_Draw(sf::RenderWindow &window);
		std::vector<sf::IntRect> getCollideRects(){return collideRects;};
};

#endif