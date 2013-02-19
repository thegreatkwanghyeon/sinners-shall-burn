#include "battle.h"
#include "stdio.h"

Battle::Battle(){
	puzzle = new Puzzle();
}

void Battle::update(){
	puzzle->update();
}

void Battle::draw(sf::RenderWindow &window){
	puzzle->draw(window);
}