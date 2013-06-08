#include "scenemanager.h"


int main(void){
	sf::RenderWindow window(sf::VideoMode(1280,720), "SFML");	
	SceneManager *sceneManager = new SceneManager();

	 window.setFramerateLimit(60);
	 sf::Clock clock;
	 sf::View view;
	 view.reset(sf::FloatRect(0, 0, 1280, 700));
	 float lastTime = 0;

	while(window.isOpen()){
		sf::Event Event;

		while (window.pollEvent(Event)){
			if(Event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				window.close();
			}
		
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
				view.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
					sceneManager->setScene(new TitleScene());
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
				view.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
					sceneManager->setScene(new GameScene());
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
				view.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
				sceneManager->setScene(new ShaderScene());
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
				view.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
					//sceneManager->setScene(new Battle(2));
			}	
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
					view.setViewport(sf::FloatRect(0.f, 0.f, 2.0f, 2.0f));
					sceneManager->setScene(new RayCastingScene());
			}	
		sceneManager->update(Event);
		}

		float currentTime = clock.restart().asSeconds();
        float fps = 1.f / currentTime ;
        lastTime = currentTime;

		sf::Text textFps;
		sf::Font font;
		char stringFps[20];

		font.loadFromFile("font/font.ttf");
		textFps.setFont(font);
		sprintf(stringFps, "FPS = %.0f", fps);
		textFps.setString(stringFps);

	

		window.clear();
		window.setView(view);
		sceneManager->update(Event);
		sceneManager->draw(window);

		window.draw(textFps);
		window.display();

		

	}
	return EXIT_SUCCESS;
}