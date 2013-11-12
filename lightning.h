#ifndef __lightning__
#define __lightning__

#include "stdafx.h"
#include <list>
#include "line.h"
#include "well512.h"

using namespace std;

class Lightning{
	private : 

		Well512* random;

		float detail;
		float displacement;
		float thickness;

		int r, g, b, a;

		Vector2i startPosition;
		Vector2i endPosition;

		void drawLightning(RenderWindow &window, Vector2i startPosition, Vector2i endPosition, float displace);


	public : 

		Lightning();
		~Lightning(){
			delete random;
		}

		void setStartPosition(float x, float y);
		void setEndPosition(float x, float y);
		void setThcikness(float thickness);
		void setDetail(float detail);
		void setDisplacement(float displacement);
		void setColor(int r, int g, int b);

		void update();
		void draw(RenderWindow &window);
};

#endif