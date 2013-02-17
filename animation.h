#ifndef __animation__
#define __animation__

#include <SFML/Graphics.hpp>

#include "tileset.h"

class Animation{
	private:
		TileSet                   *tileSet;
		sf::Texture               texture;
		sf::Vector2i              interval;
		sf::Vector2i 			  intervalPosition;
		int 					  numberOfTile;
		std::vector<sf::Texture > textures;
		int                       currentTexture;
		int                       currentTileX;
		int                       currentTileY;
		int                       tileNum;
		int                       endTileNum;
		float                     tmpElapsedTime;
		float                     _speed;
		bool                      isPlay;
		
		sf::Clock                 eTime;
		sf::Time                  deltaTime;


		void play(sf::Sprite *sprite, bool tile, sf::Time deltaTime);		


	public:
		Animation();
		~Animation(){delete tileSet;}
		void setSpeed(float speed);		
		void addFrame(std::string path);
		void setTileRange(sf::Vector2i _intervalPosition, int _numberOfTile);
		void addTile(std::string path, int _tileWidth, int _tileHeight);
		void update(sf::Sprite *sprite, bool tile);
		void playAnimation();
		void playAnimationAt(int number);
		void stopAnimation();
		void stopAnimationAt(int num);
		//sf::Vector2i tileSize;

		int tileSizeX, tileSizeY;
};

#endif