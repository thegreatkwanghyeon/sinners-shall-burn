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

		Vector2i startPosition;
		Vector2i endPosition;

		void drawLightning(RenderWindow &window, Vector2i startPosition, Vector2i endPosition, float displace);

	public : 
		Lightning(Vector2i startPosition, Vector2i endPosition, float thickness, float detail, float displacement);
		~Lightning(){
			delete random;
		}

		void update();
		void draw(RenderWindow &window);
};