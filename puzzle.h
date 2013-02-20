#ifndef __puzzle__
#define __puzzle__
#include "stdafx.h"

#include <stdlib.h>
#include <time.h>

//#include "tileset.h"
#include "pdata.h"

#define PuzzleSize 8
#define PuzzleKind 7
#define StackSize 5
//---
#define PStartX 30
#define PStartY 30
#define PBlockSize 50//이거 pdata에도 있음...

class Puzzle{
	private:
		sf::Vector2i  position;
		sf::Vector2i  mousePosition;
		sf::Vector2i temp;

		sf::Clock eTime;
		sf::Time deltaTime;
		bool flag,direction;
		int tempNum;

	public:
		Puzzle();
		~Puzzle();
		void update();
		void draw(sf::RenderWindow &window);

		int tileSizeX, tileSizeY;

		PData *data[PuzzleSize+1][PuzzleSize+1];
		int clickN;
		sf::Vector2i clickStack[PuzzleSize*PuzzleSize+1];

		int checkPuzzle();
		void makePuzzle();
		void movePuzzle(sf::Vector2i tp, int d);

//---스택
		PData *stack[StackSize];
		int stackNum;
		void stackInput(int num);
//---콤보
		int combo[10];
		int comboNum;
};
#endif