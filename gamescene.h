#ifndef __gamescene__
#define __gamescene__

#include "scenebase.h"
#include "map.h"
#include "uiscene.h"
#include "player.h"

#include "button.h"
#include "battle.h"



class GameScene : public SceneBase{
	private:
		//Character *character;
		Map *map;
		UiScene *uiscene;
		Player *player;

		Button *button;
		Battle *battle;
		bool flag;

	public:
		GameScene();
		~GameScene(){delete map; delete uiscene; delete player;}
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);
		
};

#endif