#ifndef __clearscene__
#define __clearscene__

#include "scenebase.h"
#include "particlesystem.h"
#include "button.h"

class ClearScene : public SceneBase{
	private:
		sf::Text text;
		sf::Font font;
		sf::Texture texture;
		sf::Sprite sprite;

		Button* startButton;
		Button* endButton;

		bool sceneFlag,endFlag;

	public:
		ClearScene();
		virtual ~ClearScene();
		virtual void update(sf::Event &event);
		virtual void draw(sf::RenderWindow &window);
		virtual int changeScene();

};

#endif