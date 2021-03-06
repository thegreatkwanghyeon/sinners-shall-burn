#include "line.h"

Line::Line(){
}

void Line::setStartPosition(float x, float y){
	startPosition_x = x;
	startPosition_y = y;
}

void Line::setEndPosition(float x, float y){
	endPosition_x = x;
	endPosition_y = y;
}

void Line::setThickness(float thickness){
	this->thickness = thickness;
}

void Line::initialize(){
	float length = sqrt((endPosition_x - startPosition_x) * (endPosition_x - startPosition_x) + (endPosition_y - startPosition_y) * (endPosition_y - startPosition_y));
	float rot = atan2(endPosition_y - startPosition_y, endPosition_x - startPosition_x);

	line.setFillColor(Color(r,g,b));
	line.setSize(Vector2f(length, thickness));
	line.setPosition(startPosition_x, startPosition_y);
	line.setRotation(rot * 180/M_PI);
}

void Line::setColor(int r, int g, int b){
	this->r = r;
	this->g = g;
	this->b = b;
}

void Line::update(){

}

void Line::draw(RenderWindow &window){
	window.draw(line);
}

void Line::draw(RenderWindow &window, sf::Shader &effect){
	window.draw(line, &effect);	
}