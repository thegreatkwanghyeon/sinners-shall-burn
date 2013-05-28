#include "scenemanager.h"


int main(void){
	sf::RenderWindow window(sf::VideoMode(1280,720), "SFML");	
	SceneManager *sceneManager = new SceneManager();

	 window.setFramerateLimit(60);
	 sf::Clock clock;
	 float lastTime = 0;

	while(window.isOpen()){
		sf::Event Event;

		while (window.pollEvent(Event)){
			if(Event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				window.close();
			}
		
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
					sceneManager->setScene(new TitleScene());
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
					sceneManager->setScene(new GameScene());
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
				sceneManager->setScene(new ShaderScene());
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
					//sceneManager->setScene(new Battle(2));
			}	
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
					sceneManager->setScene(new RayCastingScene());
			}	
		sceneManager->update(Event);
		}

		float currentTime = clock.restart().asSeconds();
        float fps = 1.f / currentTime ;
        lastTime = currentTime;

		window.clear();
		sceneManager->update(Event);
		sceneManager->draw(window);
		printf("%f\n", fps);
		window.display();

		

	}
	return EXIT_SUCCESS;
}