#ifndef __player__
#define __player__

#include "entity.h"
#include "tinyxml.h"
#include "global.h"

class Player : public Entity {
	private:
		TiXmlDocument stats;
		sf::Text txtStats;
		sf::Font font;

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
		Player(const char *_path , sf::Vector2i _position);
		virtual ~Player(){}

		virtual void update();
		virtual void draw(sf::RenderWindow &window);
};

#endif