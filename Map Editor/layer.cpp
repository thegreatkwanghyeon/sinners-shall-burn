#include "layer.h"

void Layer::setTexture(sf::Texture mainTexture){
	selector.initialize(mainTexture);
	putter.initialize(mainTexture);
}

void Layer::update(sf::RenderWindow &window){
	selector.select(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	putter.putTile(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, selector.getSelectedTile());	
}

void Layer::draw(sf::RenderWindow &window){
	putter.draw(window);
	selector.draw(window);
}