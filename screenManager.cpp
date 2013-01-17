#include "screenManager.h"

GameScreen *currentScreen;

ScreenManager::ScreenManager(){

}

ScreenManager &ScreenManager::getInstance(){
	static ScreenManager instance;
	return instance;
}

void ScreenManager::initialize(){
	currentScreen = new TitleScreen();
}

void ScreenManager::loadContent(){
	currentScreen->loadContent();
}

void ScreenManager::update(){
	currentScreen->update();
}

void ScreenManager::draw(sf::RenderWindow &window){
	currentScreen->draw(window);
}

void ScreenManager::setScreen(GameScreen *screen){
	currentScreen->unloadContent();
	delete currentScreen;
	currentScreen = screen;
	currentScreen->loadContent();
}