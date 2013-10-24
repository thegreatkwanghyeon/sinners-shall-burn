#ifndef __gamescene__
#define __gamescene__

#include "raycastingscene.h"
#include "battle.h"
#include "player.h"
#include "enemy.h"
#include "button.h"


class GameScene : public SceneBase{
	private:
		RayCastingScene* rayCastingScene;
		Battle *battle;
		Player *player;
		Player **pPlayer;
		MakeMap *makemap;

		sf::Font font;
		sf::Text text;

		Button *overButton;

		std::vector <Enemy*> enemy;
		std::vector <Enemy*> *pEnemy;

		sf::Sprite sprite;
		sf::Image texture;

		bool isOver,changeFlag;


		bool isBattle;
		int nowEnemy;

		int floorNum;
		
		int worldMap[MapY+100][MapX+100];

		void makeEnemys();//�� ������ ���� �и�����...
		sf::Vector2f translatePosition(float _x, float _y);
	public:
		GameScene();
		~GameScene(){}
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);
		int changeScene();//���ӿ���, Ÿ��Ʋ�� ���ư��� ���� ��Ȳ�� ���ο� �ź��� ����?
};

#endif