#ifndef __gamescene__
#define __gamescene__

#include "raycastingscene.h"
#include "battle.h"
#include "player.h"
#include "enemy.h"


class GameScene : public SceneBase{
	private:
		RayCastingScene* rayCastingScene;
		Battle *battle;
		Player *player;
		Player **pPlayer;

		std::vector <Enemy*> enemy;
		std::vector <Enemy*> *pEnemy;

		sf::Sprite sprite;
		sf::Image texture;

		bool isOver;


		bool isBattle;
		int nowEnemy;
	public:
		GameScene();
		~GameScene(){}
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);
		int changeScene();//게임오버, 타이틀로 돌아가기 등의 상황서 메인에 신변경 전달?
};

#endif