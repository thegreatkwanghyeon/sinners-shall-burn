#ifndef __puzzle__
#define __puzzle__
//첫 sfml 코딩이라 일단 버튼 헤더랑 cpp 참조해서 만들었다. 수정 필요.
//구현 : 퍼즐 생성, 출력.
#include <SFML/Graphics.hpp>
#include <cstdio>

#include "tileset.h"

#define PuzzleSize 8//사이즈.
#define PuzzleKind 7//PuzzleKind만큼의 형태가 있다. 이건 나중에 고침.

class Puzzle{
	private:
		sf::Sprite sprite;

		sf::Texture   texture;
		sf::Vector2i  position;
		sf::Vector2i  mousePosition;

		TileSet *tileset;

		int data[11][11];//일부러 여유 좀 나게 만듬. 실제 크기는 8*8
		//bool isMouseOver (sf::Vector2i _mousePosition);
		//bool isMouseClicked ();

	public:
		Puzzle();
		~Puzzle();
		void update();
		void draw(sf::RenderWindow &window);
		int make_RandomNum(sf::Clock time_user, int i, int j);
		void addTile(std::string path, int _tileWidth, int _tileHeight);

		int tileSizeX, tileSizeY;

		//bool checkPuzzle();

		//bool checkMouseClick();

};
#endif