#ifndef __gamescene__
#define __gamescene__

#include "scenebase.h"

#include "character.h"
#include "map.h"

class GameScene : public SceneBase{
	private:
		Character *character;
		Map *map;
	public:
		GameScene();
		~GameScene(){delete character; delete map;}
		void update();
		void draw(sf::RenderWindow &window);
		
};

#endif