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
		int dot;//damage over time
		int guard;//추가 방어
		int acc;//추가 명중률

	public:
		int element[30],useElement[10];
		Player();
		~Player(){delete skill;};

		void update();
		void draw(sf::RenderWindow &window);
		void setHP(int num);
		void setMaxHP(int num);
		void setDot(int num);
		void setAcc(int num);
		void setGuard(int num);
		int getHP();
		int getMaxHP();
		int getDot();
		int getAcc();
		int getGuard();

		Skill *skill;
};

#endif