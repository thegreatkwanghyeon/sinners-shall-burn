#ifndef __titlescene__
#define __titlescene__

#include "scenebase.h"
#include "particlesystem.h"
#include "button.h"

class TitleScene : public SceneBase{
	private:
		sf::Text text;
		sf::Font font;

		ParticleSystem* particle;
		Button* startButton;
		Button* endButton;

		bool sceneFlag,endFlag;

	public:
		TitleScene();
		virtual ~TitleScene();
		virtual void update(sf::Event &event);
		virtual void draw(sf::RenderWindow &window);
		virtual int changeScene();

};

#endif