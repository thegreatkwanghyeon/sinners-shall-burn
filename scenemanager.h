#ifndef __scenemanager__
#define __scenemanager__

#include "scenebase.h"
#include "gamescene.h"
#include "titlescene.h"
#include "shaderscene.h"
#include "battle.h"

class SceneManager{
	private:
		SceneBase *currentScene;
	public:
		SceneManager();
		~SceneManager();
		void setScene(SceneBase *scene);
		void update();
		void draw(sf::RenderWindow &window);
};

#endif