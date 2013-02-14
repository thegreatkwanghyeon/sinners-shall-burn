#ifndef __titlescene__
#define __titlescene__

#include "scenebase.h"
#include "puzzle.h"

class TitleScene : public SceneBase{
	private:
		sf::Text text;
		sf::Font font;

		Puzzle *puzzle;
	public:
		TitleScene();
		virtual ~TitleScene();
		virtual void update();
		virtual void draw(sf::RenderWindow &window);

};

#endif