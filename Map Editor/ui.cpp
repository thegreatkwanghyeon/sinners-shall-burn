#include "ui.h"

UI::UI(){
	vLine.setSize(sf::Vector2f(5, MAPHEIGHT));

	vLine.setPosition(MAPWIDTH, 0);

	vLine.setFillColor(sf::Color::Red);

	hLine.setSize(sf::Vector2f(MAPWIDTH + 200, 5));

	hLine.setPosition(0, MAPHEIGHT);

	hLine.setFillColor(sf::Color::Red);	
}

void UI::draw(sf::RenderWindow &window){
	window.draw(vLine);
	window.draw(hLine);
}