#ifndef __puzzle__
#define __puzzle__
#include "stdafx.h"

#include <stdlib.h>
#include <time.h>

#include "tileset.h"
#include "pdata.h"
#include "button.h"
#include "gauge.h"

#define PuzzleSize 8
#define PuzzleKind 7
#define StackSize 5
//---
#define PStartX 500
#define PStartY 415
class Puzzle{
	private:
		sf::Vector2i  position;
		sf::Vector2i  mousePosition;
		sf::Vector2i temp;

		sf::Font font;
		sf::Text text;

		sf::Sprite   sprite,bgSprite;
		sf::Texture  texture,bgTexture;

		sf::Clock eTime;
		sf::Time deltaTime;

		//float limit1;

		bool flag;
		bool move;
		bool change;
		bool hint;
		int tempNum;
		int reNum;
		int breakStack[PuzzleSize+5];
		int chkBreak[PuzzleSize+5][PuzzleSize+5];

		float plusDamage;

		int PuzzleElement[PuzzleKind+1];

		TileSet *tileset;
		Button *button;
		Button *reButton;

		Gauge *hGauge;

		sf::Clock hTime,reTime;

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
		void checkPuzzleMore();//더 터질게 있나? 걍 그런거
		void setElement(int Element[]);

		float getPlusDamage();
		void setPlusDamage(float _damage);

//---스택
		PData *stack[StackSize+5];
		int stackNum;
		void stackInput(int num);
		void cleanStack();
//---콤보
		int combo[10];
		int comboNum;
//---re버튼
		int getReNum();
		void setReNum(int num);
};
#endif