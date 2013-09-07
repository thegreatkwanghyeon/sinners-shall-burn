#ifndef __battle__
#define __battle__

#include "scenebase.h"
#include "tinyxml.h"
#include "puzzle.h"
#include "global.h"
#include "player.h"
#include "skill.h"
#include "button.h"
#include "tileset.h"
#include "tooltip.h"
#include "gauge.h"
#include "enemy.h"

#define StackNum 5
#define ViewSkill 6

struct Monster{
	sf::Text name;
	int hp;
};

class Battle : public SceneBase{
	private:
		TiXmlDocument stats;
		sf::Font font;

		sf::Sprite   sprite;
		sf::Texture  texture;
		TileSet *tileset;
		Enemy *enemy;
		Player *player;

		sf::Clock deltaClock;
		bool keyEvent;
		bool isBattle;

		Monster monster;
		Skill *skill;
		Button *button[ViewSkill+1];
		Tooltip *tooltip[ViewSkill+1];

		Gauge *hpGauge;
		Gauge *enemyGauge;

		int code;
		int canUseSkill[ViewSkill+1];
		//int useCnt;

		//Character *character;
		Puzzle *puzzle;

	public:
		Battle(int Code, Player* _player);
		~Battle(){delete puzzle;}
		void update(sf::Event &event);
		int getResult();
		int makeCode(int s, int e);
		void draw(sf::RenderWindow &window);
		void useSkill(int num);
		void startBattle(Enemy* _enemy);
};

#endif