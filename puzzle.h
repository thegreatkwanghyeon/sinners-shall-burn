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

		sf::Text text1,text2,text3;
		sf::Font font;

		float limit1;
		bool limit2, limit3;//텍스트 3개에 사용되는, 각각의 카운터?

		bool flag;
		bool move;
		bool change;
		int tempNum;
		int breakStack[PuzzleSize];
		int chkBreak[PuzzleSize][PuzzleSize];

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
		void movePuzzle();
		void checkPuzzleMore();//더 터질게 있나? 걍 그런거

//---스택
		PData *stack[StackSize];
		int stackNum;
		void stackInput(int num);
//---콤보
		int combo[10];
		int comboNum;
};
#endif