#ifndef __scenebase__
#define __scenebase__

#include <SFML/Graphics.hpp>

class SceneBase{
	private:
	public:
		SceneBase();
		~SceneBase();
		virtual void update();
		virtual void draw(sf::RenderWindow &window);
};

#endif