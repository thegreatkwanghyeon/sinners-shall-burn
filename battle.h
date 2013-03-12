#ifndef __battle__
#define __battle__

#include "scenebase.h"
#include "tinyxml.h"
#include "puzzle.h"
#include "global.h"
//#include "player.h"

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

		Monster list[100];

		int code;

		//Character *character;
		Puzzle *puzzle;

	public:
		Battle(int Code);
		~Battle(){delete puzzle;}
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);
		
};

#endif