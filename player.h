#ifndef __player__
#define __player__

#include "entity.h"
#include "tinyxml.h"
#include "global.h"
#include "skill.h"

class Player : public Entity {
	private:

	public:
		enum Stat{
			hp,//체력 
			attack,//공격력
			defense,//방어력
			critical,//치명타율
			agility,//공격속도
			accuracy,//명중율
		};
		int status[7];//한칸은 여유분
		int element[30],useElement[10];
		Player(const char *_path , sf::Vector2i _position);
		virtual ~Player(){delete skill;};

		virtual void update(std::vector<sf::FloatRect> collideRects);
		virtual void draw(sf::RenderWindow &window);

		Skill *skill;
};

#endif