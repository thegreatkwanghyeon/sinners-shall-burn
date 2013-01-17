#include "screenManager.h"
#include <SFML/Graphics.hpp>
int main(){
	sf::RenderWindow Window(sf::VideoMode(ScreenWidth, ScreenHeight, 32),"Ddong Game");
	//ScreenWidth, ScreenHeight 매크로 상수는 screenManager.h 에 정의되어 있음

	ScreenManager::getInstance().initialize();
	ScreenManager::getInstance().loadContent();

	while(Window.isOpen()){
		sf::Event event;

		if(Window.pollEvent(event)){
			if(event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
				Window.close();

			if(event.key.code == sf::Keyboard::Num1)
				ScreenManager::getInstance().setScreen(new MenuScreen);
			else if(event.key.code == sf::Keyboard::Num2)
				ScreenManager::getInstance().setScreen(new TitleScreen);
		}



		Window.clear();

		ScreenManager::getInstance().update();
		ScreenManager::getInstance().draw(Window);

		Window.display();
	}
	return 0;
}