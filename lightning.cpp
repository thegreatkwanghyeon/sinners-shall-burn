#include "lightning.h"

Lightning::Lightning(){
	random = new Well512();
	effect.loadFromFile("shaders/blur.frag",sf::Shader::Fragment);
	effect.setParameter("texture",sf::Shader::CurrentTexture);
	//effect.setParameter("blur_radius", 0.08f);
}

void Lightning::setStartPosition(float x, float y){
	startPosition.x = x;
	startPosition.y = y;
}

void Lightning::setEndPosition(float x, float y){
	endPosition.x = x;
	endPosition.y = y;
}

void Lightning::setDetail(float detail){
	this->detail = detail;
}

void Lightning::setThcikness(float thickness){
	this->thickness = thickness;
}

void Lightning::setDisplacement(float displacement){
	this->displacement = displacement;
}

void Lightning::setColor(int r, int g, int b){
	this->r = r;
	this->g = g;
	this->b = b;
}

void Lightning::drawLightning(RenderWindow &window, Vector2i startPosition, Vector2i endPosition, float displace){
	if (displace < detail){
		Line line;
		line.setColor(r, g, b);
		line.setStartPosition(startPosition.x, startPosition.y);
		line.setEndPosition(endPosition.x, endPosition.y);
		line.setThickness(thickness);
		line.initialize();
		line.draw(window, effect);
	}
	else{
		float mid_x = ((startPosition.x + endPosition.x) / 2) + (random->NextFloat(-0.5, 0.5)) * displace;
		float mid_y = ((startPosition.y + endPosition.y) / 2) + (random->NextFloat(-0.5, 0.5)) * displace;

		drawLightning(window, startPosition, Vector2i(mid_x, mid_y), displace / 2);
		drawLightning(window, endPosition, Vector2i(mid_x, mid_y), displace / 2);
	}
}

void Lightning::update(){

}

void Lightning::draw(RenderWindow &window){
	drawLightning(window, startPosition, endPosition, displacement);
}