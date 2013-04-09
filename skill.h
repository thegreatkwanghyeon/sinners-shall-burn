#ifndef __skill__
#define __skill__

#include "tinyxml.h"
#include "global.h"
#include "stdafx.h"

#define StackNum 5
#define SkillMax 200

struct SkillData{
	sf::Text name;
	sf::Text intro;
	sf::Text effect;
	int need[30],needCode;
	int damage;
	int heal, poison;
	int guard;
	int distance;
	int distanceACK;//�Է¹������� ���Ļ� int�� ����.
	int Estat[30],Pstat[30];
	int code;
	int acc;
	int field;

	//bool use;
	bool have;
};

class Skill{
	private:
		TiXmlDocument xmls;
	public:
		Skill();
		~Skill(){};

		void setHave(int num);
		//void getNeed(int m[]);
		void translate(int num, int m[]);
		//int makeCode(int s, int e);
		SkillData data[SkillMax];

		int skillNum;
		int check[100];
};

#endif