#ifndef __battle__
#define __battle__

#include "scenebase.h"
#include "tinyxml.h"
#include "puzzle.h"
#include "global.h"
#include "player.h"

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
struct Skill{
	sf::Text name;
	sf::Text intro;
	sf::Text effect;
	int need[30];
	int damage;
	int heal, poison;
	int Estat[30],Pstat[30];
	int code;
};

class Battle : public SceneBase{
	private:
		TiXmlDocument stats;
		sf::Font font;

		Monster monster;
		Skill skill[100];

		int code;
		int check[100];

		//Character *character;
		Puzzle *puzzle;

	public:
		Battle(int Code, Player* p);
		~Battle(){delete puzzle;}
		void update(sf::Event &event);
		int GetResult();
		void translate(int num, int m[]);
		void draw(sf::RenderWindow &window);		
		int skillNum;
};

#endif