#ifndef __player__
#define __player__

#include "entity.h"
#include "tinyxml.h"
#include "global.h"
#include "skill.h"

class Player{
	private:
		int hp;
		int maxHp;

	public:
		int element[30],useElement[10];
		Player();
		~Player(){delete skill;};

		void update();
		void draw(sf::RenderWindow &window);
		void setHP(int num);
		void setMaxHP(int num);
		int getHP();
		int getMaxHP();

		Skill *skill;
};

#endif