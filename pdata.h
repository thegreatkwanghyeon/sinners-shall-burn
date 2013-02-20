#ifndef __pdata__
#define __pdata__
#include "stdafx.h"

#include <stdlib.h>
#include <time.h>

#include "animation.h"

#define PBlockSize 50

class PData{//퍼즐 애니메이션 담당.
	private:
		sf::Sprite sprite;
		Animation *animation;

		
	public:
		int num;
		bool is_click;
		bool is_break;

		PData(float _x, float _y);
		~PData(){delete animation;};
		void init_animation();
		void update();
		void draw(sf::RenderWindow &window);
		int getLocation();
};
#endif