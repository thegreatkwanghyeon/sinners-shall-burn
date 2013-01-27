#ifndef __gamescene__
#define __gamescene__

#include "scenebase.h"
#include "character.h"
#include "map.h"
#include "uiscene.h"

#include <cstdio>

class GameScene : public SceneBase{
	private:
		Character *character;
		Map *map;
		UiScene *uiscene;

	public:
		GameScene();
		~GameScene(){delete character; delete map; delete uiscene;}
		void update();
		void draw(sf::RenderWindow &window);
		
};

#endif