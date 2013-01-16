#include <SFML/Graphics.hpp>
#include "character.h"

int main(void){
	sf::RenderWindow window(sf::VideoMode(800,600), "SFML");
	Character character(0.0, 0.0);

	while(window.isOpen()){
		sf::Event Event;

		while (window.pollEvent(Event)){
			if(Event.type == sf::Event::Closed){
				window.close();
			}

			if(Event.type == sf::Event::KeyPressed){
				if(Event.key.code == sf::Keyboard::Escape)
					window.close();
			}
		}

		window.clear();
		character.Draw(window);	
		window.display();
	}
	return EXIT_SUCCESS;
}