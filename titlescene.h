#ifndef __titlescene__
#define __titlescene__

#include "scenebase.h"
#include "particleengine.h"

class TitleScene : public SceneBase{
	private:
		sf::Text text;
		sf::Font font;

		ParticleEngine* particle;

	public:
		TitleScene();
		virtual ~TitleScene();
		virtual void update(sf::Event &event);
		virtual void draw(sf::RenderWindow &window);

};

#endif