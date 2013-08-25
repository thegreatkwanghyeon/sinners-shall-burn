#ifndef __pdata__
#define __pdata__
#include "stdafx.h"

#include <stdlib.h>
#include <time.h>

#include "animation.h"

#define PBlockSize 35

class PData{//퍼즐 애니메이션 담당.
	private:
		sf::Sprite sprite;
		Animation *animation;

		
	public:
		int num;
		bool is_click;
		bool is_break;
		int x,y;

		PData(int _x, int _y);
		~PData(){delete animation;};
		void init_animation();
		void init_position(int _x, int _y);
		void update();
		void draw(sf::RenderWindow &window);
		int getLocation();
};
#endif