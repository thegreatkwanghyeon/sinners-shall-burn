#ifndef pausescene
#define puasescene

#include "stdafx.h"
#include "scenebase.h"


class PauseScene : public SceneBase{
	private:

	public:

		PauseScene();
		~PauseScene(){};
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);
};


#endif
