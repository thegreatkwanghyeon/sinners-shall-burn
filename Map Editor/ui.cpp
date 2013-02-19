#include "ui.h"

UI::UI(){
	vLine.setSize(sf::Vector2f(10, MAPHEIGHT));

	vLine.setPosition(MAPWIDTH, 0);

	vLine.setFillColor(sf::Color::Red);

	hLine.setSize(sf::Vector2f(MAPWIDTH + 500, 10));

	hLine.setPosition(0, MAPHEIGHT);

	hLine.setFillColor(sf::Color::Red);	

	bottomTexture.loadFromFile("tiles/bottom.png");
	rightTexture.loadFromFile("tiles/right.png");

	bottom.setTexture(bottomTexture);
	right.setTexture(rightTexture);
	bottom.setPosition(0, MAPHEIGHT);
	right.setPosition(MAPWIDTH, 0);

}

void UI::draw(sf::RenderWindow &window){
	window.draw(bottom);
	window.draw(right);
	window.draw(vLine);
	window.draw(hLine);
}