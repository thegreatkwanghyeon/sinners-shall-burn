#ifndef __battle__
#define __battle__

#include "scenebase.h"
#include "tinyxml.h"
#include "puzzle.h"
#include "global.h"
//#include "player.h"

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