#ifndef __storyscene__
#define __storyscene__

#include "scenebase.h"
#define Endstory 4

class StoryScene : public SceneBase{
	private:
		sf::Texture texture[10];
		sf::Sprite sprite;
		sf::Clock delta;

		sf::Font font;
		sf::Text text;
		int alpha;

		sf::RectangleShape rec;

		int storyNum;
		bool isPlus;

	public:
		StoryScene();
		virtual ~StoryScene();
		virtual void update(sf::Event &event);
		virtual void draw(sf::RenderWindow &window);
		virtual int changeScene();
};

#endif