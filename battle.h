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
#include "particlelist.h"

#define StackNum 5
#define ViewSkill 6
#define skillEffectTime 1.5
#define puzzleLimit 300//30초

enum{
	normal,playerSkill,enemySkill,checkSkill
};
class Battle : public SceneBase{
	private:

		typedef struct{
			sf::String statusName;
			int damagePerTurn;
			unsigned int remainedTurn;
		}statusEffect;

		std::vector<statusEffect> statusEffects;

		TiXmlDocument stats;
		sf::Font font;
		sf::Text text,eText;
		sf::Clock limitTime;
		sf::Clock skillTime;
		sf::Clock puzzleTime;
		char plusString[100];

		sf::Sprite   sprite,faceSprite,skillBGSprite;
		sf::Texture  texture, face,skillBG;
		TileSet *tileset;
		TileSet *faceTileset;
		Enemy *enemy;
		Player **player;

		ParticleList *particle;
		int useSkillNow;
		bool battleResult;

		sf::Clock deltaClock;
		bool keyEvent;
		bool isBattle;
		bool isMiss;
		int useCnt;

		Skill *skill;
		Button *button[ViewSkill+1];
		Tooltip *tooltip[ViewSkill+1];

		Gauge *hpGauge;
		Gauge *enemyGauge;
		Gauge *timeGauge;

		int code;
		int canUseSkill[ViewSkill+1];

		int sceneNum;

		bool subSkill;//몹이 서브스킬 발동시 켜는 bool?

		Puzzle *puzzle;

		void playerSkillUpdate();
		void enemySkillUpdate();
		void checkSkillUpdate();
	public:
		Battle(Player** _player);
		~Battle();
		void update(sf::Event &event);
		bool getResult();
		int makeCode(int s, int e);
		void draw(sf::RenderWindow &window);
		void useSkill(int num);
		void startBattle(int _code);
		bool getState();//현재 이펙트 진행중이거나 기타 상황이어서 일시정지를 할 수 없는 경우 false 리턴
		Puzzle* getPuzzle();
};

#endif