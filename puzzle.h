#ifndef __puzzle__
#define __puzzle__
//첫 sfml 코딩이라 일단 버튼 헤더랑 cpp 참조해서 만들었다. 수정 필요.
//구현 : 퍼즐 생성, 출력.
#include <SFML/Graphics.hpp>
#include <cstdio>
#include <stdlib.h>
#include <time.h>

//#include "tileset.h"
#include "animation.h"

#define PuzzleSize 8//사이즈.
#define PuzzleKind 7//PuzzleKind만큼의 형태가 있다. 이건 나중에 고침.
#define StackSize 5//임시값
//---
#define PStartX 0//퍼즐이 시작되는 곳의 X값
#define PStartY 0//퍼즐이 시작되는 곳의 Y값
#define PBlockSize 50//퍼즐 한 블록당 사이즈. 정사각형이니까 하나만 만듬.

class PData{//퍼즐로 쓸 클래스. 딱히 다른 파일까지 갈꺼없이 구조체처럼 쓸라고 만듬.
	private:
		sf::Sprite sprite;
		Animation *animation;

		
	public:
		int num;//퍼즐의 값
		bool is_click;//클릭되었는지 체크하는 부분.

		PData(float _x, float _y){
			animation=new Animation();
			sprite.setPosition(_x, _y);
			animation->addTile("img/PuzzleAnimation.PNG",PBlockSize,PBlockSize);
			animation->setSpeed(0.2);
			animation->setTileRange(sf::Vector2i(1,1), 4);//디폴트.
			is_click=false;
		}
		void init_animation(){
			if(is_click == true){
				animation->setTileRange(sf::Vector2i(1,5),3);
			}else{
				switch(num){
					case -1 : animation->setTileRange(sf::Vector2i(5,5),1);break; //빈 스택 표시용.
					case 0 : animation->setTileRange(sf::Vector2i(1,1),3);break;
					case 1 : animation->setTileRange(sf::Vector2i(1,2),3);break;
					case 2 : animation->setTileRange(sf::Vector2i(1,3),3);break;
					case 3 : animation->setTileRange(sf::Vector2i(1,4),3);break;
					case 4 : animation->setTileRange(sf::Vector2i(5,1),3);break;
					case 5 : animation->setTileRange(sf::Vector2i(5,2),3);break;
					case 6 : animation->setTileRange(sf::Vector2i(5,3),3);break;
					default : animation->setTileRange(sf::Vector2i(5,4),3);
				}
			}
		}
		void update(){
			animation->update(&sprite, true);
		}
		void draw(sf::RenderWindow &window){//아무래도 퍼즐 각 칸의 애니메이션 등을 그 칸이 알아서 하면 재미있을거 같아서 해봄.
			window.draw(sprite);
		}
};

class Puzzle{
	private:
		//sf::Texture   texture;
		sf::Vector2i  position;
		sf::Vector2i  mousePosition;
		bool flag;
	//	TileSet *tileset;

//		int data[PuzzleSize+1][PuzzleSize+1];
		//bool isMouseOver (sf::Vector2i _mousePosition);
		//bool isMouseClicked ();

		//void swap(int n1, int n2);//포인터 주소로 받아서 즉석처리 굳굳 

	public:
		Puzzle();
		~Puzzle();
		void update();
		void draw(sf::RenderWindow &window);
	//	void addTile(std::string path, int _tileWidth, int _tileHeight);

		int tileSizeX, tileSizeY;

		PData *data[PuzzleSize+1][PuzzleSize+1];//+1은 혹시 버그날때를 대비함이다.
		int clickN;
		sf::Vector2i clickStack[PuzzleSize*PuzzleSize+1];

		int checkPuzzle();

		//bool checkMouseClick();

		///------아래부터는 스택 관련.////
		PData *stack[StackSize];//출력파트가 PDate에 구비되어 있기도 하고...걍 PData로 만듬. 여기서 따로 출력하려고 이거저거 했더니 에러나서 짜증도 났고. 히히.
		int stackNum;
		void stackInput(int num);
		//void drawStack(sf::RenderWindow &window);
};
#endif