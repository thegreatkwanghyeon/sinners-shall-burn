#include "battle.h"
#include "stdio.h"

Battle::Battle(){
	puzzle = new Puzzle();
}

void Battle::update(sf::Event &event){
	puzzle->update();
}

void Battle::draw(sf::RenderWindow &window){
	puzzle->draw(window);
}