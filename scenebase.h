#ifndef __scenebase__
#define __scenebase__

#include "stdafx.h"

class SceneBase{
	private:
	public:
		SceneBase();
		virtual ~SceneBase();
		virtual void update(sf::Event &event);
		virtual void draw(sf::RenderWindow &window);
};

#endif