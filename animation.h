#ifndef __animation__
#define __animation__

#include <SFML/Graphics.hpp>

#include "tileset.h"

class Animation{
	private:
		TileSet *tileSet;
		sf::Clock eTime;
		sf::Texture texture;
		std::vector<sf::Texture> textures;
		int currentTexture;
		int currentTileX;
		int currentTileY;
		int _speed;
		int tileNum;
		void Play(sf::Sprite *sprite, bool tile);		
	public:
		Animation();
		~Animation(){delete tileSet;}
		void setSpeed(int speed);		
		void addFrame(std::string path);
		void addTile(std::string path, int _tileWidth, int _tileHeight);
		void update(sf::Sprite *sprite, bool tile){Play(sprite, tile);}
		sf::Vector2i tileSize;
};

#endif