#ifndef __battle__
#define __battle__

#include "scenebase.h"
#include "tinyxml.h"
#include "puzzle.h"
#include "global.h"
#include "player.h"

#define StackNum 5

enum Stat{
	hp,//ü�� 
	attack,//���ݷ�
	defense,//����
	critical,//ġ��Ÿ��
	agility,//���ݼӵ�
	accuracy,//������
};

struct Monster{
	sf::Text name;
	//char name[100];
	int status[7];//��ĭ�� ������
};
struct Skill{
	sf::Text name;
	sf::Text intro;
	sf::Text effect;
	int need[30],needCode;
	int damage;
	int heal, poison;
	int Estat[30],Pstat[30];
	int code;

	bool use;
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
		int makeCode(int s, int e);
		void draw(sf::RenderWindow &window);		
		int skillNum;
};

#endif