#include "stdafx.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace sf;

class Line{
private:
	Shader effect;
	RectangleShape line;
	float startPosition_x;
	float startPosition_y;

	float endPosition_x;
	float endPosition_y;

	float thickness;
	int r, g, b;
public:
	Line();
	~Line(){}

	void update();
	void draw(RenderWindow &window);
	void draw(RenderWindow &window, sf::Shader &effect);

	void setStartPosition(float x, float y);
	void setEndPosition(float x, float y);
	void setThickness(float thickness);

	void setColor(int r, int g, int b);

	void initialize();

};