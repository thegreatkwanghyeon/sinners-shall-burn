#ifndef __tileset__
#define __tileset__

#include <SFML/Graphics.hpp>

class TileSet{
	private:
		std::vector<sf::Vector2i> coords;
		sf::IntRect tileRect;
		sf::Texture texture;
		sf::Vector2i tmpcoord;
		sf::Vector2i _tileSize;
		int temp;
	public:
		TileSet(){}
		~TileSet(){}
		sf::Texture tileSet(std::string path, sf::Vector2i tileSize);
		sf::IntRect getTileSet(int tileNum);
};

#endif