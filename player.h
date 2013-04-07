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
			hp,//ü�� 
			attack,//���ݷ�
			defense,//����
			critical,//ġ��Ÿ��
			agility,//���ݼӵ�
			accuracy,//������
		};
		int status[7];//��ĭ�� ������
		int element[30],useElement[10];
		Player(const char *_path , sf::Vector2i _position);
		virtual ~Player(){delete skill;};

		virtual void update(std::vector<sf::FloatRect> collideRects);
		virtual void draw(sf::RenderWindow &window);

		Skill *skill;
};

#endif