#ifndef __animation__
#define __animation__

#include <SFML/Graphics.hpp>

#include "tileset.h"

class Animation{
	private:
		TileSet tileSet;
		sf::Clock eTime;
		sf::Texture texture;
		std::vector<sf::Texture> textures;
		sf::Vector2i tileSize;
		int currentTexture;
		int currentTileX;
		int currentTileY;
		int _speed;
		int tileNum;
	public:
		Animation();
		~Animation(){}
		void addFrame(std::string path);
		void addTile(std::string path, int _tileWidth, int _tileHeight);
		void Play(sf::Sprite *sprite, bool tile);
		void setSpeed(int speed);
};

#endif