#ifndef __titlescene__
#define __titlescene__

#include "scenebase.h"

class TitleScene : public SceneBase{
	private:
		sf::Text text;
		sf::Font font;
	public:
		TitleScene();
		~TitleScene();
		void update();
		void draw(sf::RenderWindow &window);

};

#endif