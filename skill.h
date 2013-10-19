#ifndef __skill__
#define __skill__

#include "tinyxml.h"
#include "global.h"
#include "stdafx.h"

#define StackNum 5
#define SkillMax 200
#define ElementNum 15

struct SkillData{
	sf::String name;
	sf::String effect;
	int need[ElementNum],needCode;
	int damage;
	int pdamage;
	int guard;
	int code;
	int acc;
	int animationNum;

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