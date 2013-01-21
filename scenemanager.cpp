#include "scenemanager.h"

SceneManager::SceneManager(){
	currentScene = new TitleScene();
}

SceneManager::~SceneManager(){
	
}

void SceneManager::setScene(SceneBase *scene){
	delete currentScene;
	currentScene = scene;
}

void SceneManager::update(){
	currentScene->update();
}

void SceneManager::draw(sf::RenderWindow &window){
	currentScene->draw(window);
}