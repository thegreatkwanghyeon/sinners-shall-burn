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
#include "animation.h"

#define StackNum 5
#define ViewSkill 6

enum{
	normal,playerSkill,enemySkill,checkSkill
};
class Battle : public SceneBase{
	private:
		TiXmlDocument stats;
		sf::Font font;
		sf::Text text;
		sf::Clock limitTime;
		char plusString[100];

		sf::Sprite   sprite,faceSprite,skillSprite;
		sf::Texture  texture, face;
		TileSet *tileset;
		TileSet *faceTileset;
		Enemy *enemy;
		Player **player;

		Animation *skillEffect;
		int useSkillNow;
		bool battleResult;
		int temp,oldtemp;//코드값 임시 저장소

		sf::Clock deltaClock;
		bool keyEvent;
		bool isBattle;
		int useCnt;

		Skill *skill;
		Button *button[ViewSkill+1];
		Tooltip *tooltip[ViewSkill+1];

		Gauge *hpGauge;
		Gauge *enemyGauge;

		int code;
		int canUseSkill[ViewSkill+1];

		int sceneNum;
		//int useCnt;

		//Character *character;
		Puzzle *puzzle;

		void playerSkillUpdate();
		void enemySkillUpdate();
		void checkSkillUpdate();

	public:
		Battle(Player** _player);
		~Battle(){delete puzzle;}
		void update(sf::Event &event);
		bool getResult();
		int makeCode(int s, int e);
		void draw(sf::RenderWindow &window);
		void useSkill(int num);
		void startBattle(int _code);
};

#endif