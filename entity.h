#ifndef __entity__
#define __entity__

#include "stdafx.h"
#include "animation.h"

#define SPEED 200

struct Status{//일단 int로 함.
	int hp;//체력 
	int attack;//공격력
	int defense;//방어력
	int critical;//치명타율
	int speed;//스피드
	int Accuracy;//명중율
};

class Entity {
	protected:

		enum Direction {
			Up,
			Left,
			Down,
			Right,
		};

		enum State {
			Staying,
			Moving,
		};

		sf::Sprite sprite;
		sf::Clock eTime;
		sf::Time deltaTime;

		Status status;

		int currentDirection;
		int currentState;

		Animation *animation;
		void move(sf::Vector2i _direction);
		void setDirection(int _direction);
		void setState(int _state);

	public:
		Entity(const char *_path, sf::Vector2i _position);
		virtual ~Entity(){delete animation;}
		virtual void update();
		virtual void draw(sf::RenderWindow &window);
};



#endif