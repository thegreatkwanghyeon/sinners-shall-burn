#ifndef __battle__
#define __battle__

#include "scenebase.h"
#include "tinyxml.h"
#include "puzzle.h"
#include "global.h"
#include "player.h"
#include "skill.h"

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

class Battle : public SceneBase{
	private:
		TiXmlDocument stats;
		sf::Font font;

		Monster monster;
		Skill *skill;

		int code;

		//Character *character;
		Puzzle *puzzle;

	public:
		Battle(int Code, Player* p);
		~Battle(){delete puzzle;}
		void update(sf::Event &event);
		int GetResult();
		int makeCode(int s, int e);
		void draw(sf::RenderWindow &window);
};

#endif