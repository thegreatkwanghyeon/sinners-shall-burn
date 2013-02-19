#ifndef __battle__
#define __battle__

#include "scenebase.h"
#include "puzzle.h"
//#include "player.h"

class Battle : public SceneBase{
	private:
		//Character *character;
		Puzzle *puzzle;

	public:
		Battle();
		~Battle(){delete puzzle;}
		void update();
		void draw(sf::RenderWindow &window);
		
};

#endif