#ifndef __gamescene__
#define __gamescene__

#include "raycastingscene.h"
#include "battle.h"
#include "player.h"


class GameScene : public SceneBase{
	private:
		RayCastingScene* rayCastingScene;
		Battle *battle;
		Player *player;

		bool isBattle;
	public:
		GameScene();
		~GameScene(){}
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);
};

#endif