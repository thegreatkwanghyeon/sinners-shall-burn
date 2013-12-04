#ifndef __logoscene__
#define __logoscene__

#include "scenebase.h"
#define EndLogo 2

class LogoScene : public SceneBase{
	private:
		sf::Texture texture[10];
		sf::Sprite sprite;
		sf::Clock delta;
		int alpha;

		sf::RectangleShape rec;

		int logoNum;

	public:
		LogoScene();
		virtual ~LogoScene();
		virtual void update(sf::Event &event);
		virtual void draw(sf::RenderWindow &window);
		virtual int changeScene();
};

#endif