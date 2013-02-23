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
			hp,//ü�� 
			attack,//���ݷ�
			defense,//����
			critical,//ġ��Ÿ��
			agility,//���ݼӵ�
			accuracy,//������
		};
		int status[7];//��ĭ�� ������
		Player(const char *_path , sf::Vector2i _position);
		virtual ~Player(){}

		virtual void update();
		virtual void draw(sf::RenderWindow &window);
};

#endif