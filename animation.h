#ifndef __animation__
#define __animation__

#include <SFML/Graphics.hpp>

#include "tileset.h"

class Animation{
	private:
		TileSet                   *tileSet;
		sf::Texture               texture;
		sf::Vector3i              interval;
		std::vector<sf::Texture > textures;
		int                       currentTexture;
		int                       currentTileX;
		int                       currentTileY;
		int                       tileNum;
		int                       endTileNum;
		float                     tmpElapsedTime;
		float                     _speed;

		sf::Clock                 eTime;
		sf::Time                  deltaTime;


		void play(sf::Sprite *sprite, bool tile, sf::Time deltaTime);		


	public:
		Animation();
		~Animation(){delete tileSet;}
		void setSpeed(float speed);		
		void addFrame(std::string path);
		void setInterval(sf::Vector3i _interval);
		void addTile(std::string path, int _tileWidth, int _tileHeight);
		void update(sf::Sprite *sprite, bool tile);
		sf::Vector2i tileSize;
};

#endif