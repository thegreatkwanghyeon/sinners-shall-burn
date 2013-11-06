#ifndef __titlescene__
#define __titlescene__

#include "scenebase.h"
#include "particlelist.h"
#include "button.h"
#include "slider.h"

class TitleScene : public SceneBase{
	private:
		sf::Text text;
		sf::Font font;

		//ParticleSystem* particle;
		ParticleList *particle;
		int pNum;
		sf::Clock pTime;
		bool isPress;

		Button* startButton;
		Button* endButton;

		Slider* slider;

		bool sceneFlag,endFlag;

	public:
		TitleScene();
		virtual ~TitleScene();
		virtual void update(sf::Event &event);
		virtual void draw(sf::RenderWindow &window);
		virtual int changeScene();

};

#endif