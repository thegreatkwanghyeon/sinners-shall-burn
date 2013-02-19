#ifndef __gamescene__
#define __gamescene__

#include "scenebase.h"
#include "map.h"
#include "uiscene.h"
#include "player.h"



class GameScene : public SceneBase{
	private:
		//Character *character;
		Map *map;
		UiScene *uiscene;
		Entity *player;

	public:
		GameScene();
		~GameScene(){delete map; delete uiscene; delete player;}
		void update();
		void draw(sf::RenderWindow &window);
		
};

#endif