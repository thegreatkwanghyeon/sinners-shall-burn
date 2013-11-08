#ifndef __gamescene__
#define __gamescene__

#include "raycastingscene.h"
#include "battle.h"
#include "player.h"
#include "enemy.h"
#include "button.h"
#include "pause.h"
#include "tooltip.h"

#define EnemyNum 5
#define EndStage 5
#define ChangeTime 350


class GameScene : public SceneBase{
	private:
		RayCastingScene* rayCastingScene;
		Battle *battle;
		Player *player;
		Player **pPlayer;
		MakeMap *makemap;
		Pause *pause;
		Tooltip *tooltip;

		sf::Font font;
		sf::Text text,fText;
		sf::Clock alphaTime;

		char plusString[100];

		sf::Vector2i portal;

		Button *overButton;

		std::vector <Enemy*> enemy;
		std::vector <Enemy*> *pEnemy;

		sf::Sprite sprite;
		sf::Image texture;

		bool isOver,changeFlag;
		sf::RectangleShape rec;

		bool isBattle;
		int nowEnemy;

		int alpha;

		int floorNum;
		
		int worldMap[MapY+100][MapX+100];

		void makeEnemys();//적 생성을 따로 분리했음...
		sf::Vector2f translatePosition(float _x, float _y);
	public:
		GameScene();
		~GameScene();
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);
		int changeScene();//게임오버, 타이틀로 돌아가기 등의 상황서 메인에 신변경 전달?
};

#endif