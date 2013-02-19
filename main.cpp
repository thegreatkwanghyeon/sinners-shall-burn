#include "scenemanager.h"


int main(void){
	sf::RenderWindow window(sf::VideoMode(800,600), "SFML");	
	SceneManager *sceneManager = new SceneManager();

	while(window.isOpen()){
		sf::Event Event;

		while (window.pollEvent(Event)){
			if(Event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				window.close();
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
			sceneManager->setScene(new ShaderScene());
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
				sceneManager->setScene(new GameScene());
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
				sceneManager->setScene(new TitleScene());
		}

		window.clear();
		sceneManager->update();
		sceneManager->draw(window);
		window.display();
	}
	return EXIT_SUCCESS;
}