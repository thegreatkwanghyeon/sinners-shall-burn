#ifndef __scenemanager__
#define __scenemanager__

#include "scenebase.h"
#include "gamescene.h"
#include "titlescene.h"
//#include "battle.h"
#include "raycastingscene.h"
#include "clearscene.h"
#include "logoscene.h"
#include "storyscene.h"

class SceneManager{
	private:
		SceneBase *currentScene;
	public:
		SceneManager();
		~SceneManager();
		void setScene(SceneBase *scene);
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);
		SceneBase* getCurrentScene();
};

#endif