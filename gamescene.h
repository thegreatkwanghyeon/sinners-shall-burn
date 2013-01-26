#ifndef __gamescene__
#define __gamescene__

#include "scenebase.h"
#include "character.h"
#include "map.h"
#include "button.h"

#include <cstdio>

class GameScene : public SceneBase{
	private:
		Character *character;
		Map *map;
		Button *button;
		Button *button2;
	public:
		GameScene();
		~GameScene(){delete character; delete map; delete button;}
		void update();
		void draw(sf::RenderWindow &window);
		
};

#endif