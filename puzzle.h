#ifndef __puzzle__
#define __puzzle__
#include "stdafx.h"

#include <stdlib.h>
#include <time.h>

#include "tileset.h"
#include "pdata.h"
#include "button.h"

#define PuzzleSize 8
#define PuzzleKind 7
#define StackSize 5
//---
#define PStartX 30
#define PStartY 30
#define PBlockSize 50//�̰� pdata���� ����...

class Puzzle{
	private:
		sf::Vector2i  position;
		sf::Vector2i  mousePosition;
		sf::Vector2i temp;

		sf::Sprite   sprite;
		sf::Texture  texture;

		sf::Clock eTime;
		sf::Time deltaTime;

		sf::Text text1,text2,text3;
		sf::Font font;

		float limit1;
		bool limit2, limit3;

		bool flag;
		bool move;
		bool change;
		bool hint;
		int tempNum;
		int breakStack[PuzzleSize];
		int chkBreak[PuzzleSize][PuzzleSize];

		int PuzzleElement[PuzzleKind+1];

		TileSet *tileset;
		Button *button;

	public:
		Puzzle();
		~Puzzle();
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);

		int tileSizeX, tileSizeY;

		PData *data[PuzzleSize+1][PuzzleSize+1];
		int clickN;
		int hitNum;
		sf::Vector2i clickStack[PuzzleSize*PuzzleSize+1];

		int checkPuzzle();
		void makePuzzle();
		void movePuzzle();
		void checkPuzzleMore();//�� ������ �ֳ�? �� �׷���
		void setElement(int Element[]);

//---����
		PData *stack[StackSize];
		int stackNum;
		void stackInput(int num);
//---�޺�
		int combo[10];
		int comboNum;
};
#endif