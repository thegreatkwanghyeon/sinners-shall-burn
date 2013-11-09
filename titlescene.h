#ifndef __titlescene__
#define __titlescene__

#include "scenebase.h"
#include "particlelist.h"
#include "button.h"
#include "slider.h"
#include "skill.h"
#include "lightning.h"

class TitleScene : public SceneBase{
	private:
		sf::Texture texture;
		sf::Sprite sprite;

		//ParticleSystem* particle;
		ParticleList *particle;
		int pNum;
		sf::Clock pTime;
		bool isPress;
		Skill* skill;

		Button* startButton;
		Button* endButton;

		Slider* slider;

		Lightning* lightning;

		bool sceneFlag,endFlag;

	public:
		TitleScene();
		virtual ~TitleScene();
		virtual void update(sf::Event &event);
		virtual void draw(sf::RenderWindow &window);
		virtual int changeScene();

};

#endif