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

#define StackNum 5
#define ViewSkill 5

enum Stat{
	hp,//체력 
	attack,//공격력
	defense,//방어력
	critical,//치명타율
	agility,//공격속도
	accuracy,//명중율
};

struct Monster{
	sf::Text name;
	//char name[100];
	int status[7];//한칸은 여유분
};

class Battle : public SceneBase{
	private:
		TiXmlDocument stats;
		sf::Font font;

		sf::Sprite   sprite;
		sf::Texture  texture;
		TileSet *tileset;

		Monster monster;
		Skill *skill;
		Button *button[ViewSkill+1];
		Tooltip *tooltip[5];

		int code;
		int canUseSkill[ViewSkill+1];
		//int useCnt;

		//Character *character;
		Puzzle *puzzle;

	public:
		Battle(int Code, Player* p);
		~Battle(){delete puzzle;}
		void update(sf::Event &event);
		int GetResult();
		int makeCode(int s, int e);
		void draw(sf::RenderWindow &window);
		void useSkill(int num);
};

#endif