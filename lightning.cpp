#include "lightning.h"

Lightning::Lightning(Vector2i startPosition, Vector2i endPosition, float thickness, float detail, float displacement){
	this->detail = detail;
	this->displacement = displacement;
	this->thickness = thickness;

	this->startPosition = startPosition;
	this->endPosition = endPosition;

	random = new Well512();
}

void Lightning::drawLightning(RenderWindow &window, Vector2i startPosition, Vector2i endPosition, float displace){
	if (displace < detail){
		Line line;
		line.setStartPosition(startPosition.x, startPosition.y);
		line.setEndPosition(endPosition.x, endPosition.y);
		line.setThickness(thickness);
		line.initialize();
		line.draw(window);
	}
	else{
		float mid_x = ((startPosition.x + endPosition.x) / 2) + (random->NextFloat(-0.5, 0.5)) * displace;
		float mid_y = ((startPosition.y + endPosition.y) / 2) + (random->NextFloat(-0.5, 0.5)) * displace;

		drawLightning(window, startPosition, Vector2i(mid_x, mid_y), displace/2);
		drawLightning(window, endPosition, Vector2i(mid_x, mid_y), displace / 2);
	}
}

void Lightning::update(){
	
}

void Lightning::draw(RenderWindow &window){
	drawLightning(window, startPosition, endPosition, displacement);
}