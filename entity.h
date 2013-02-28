#ifndef __entity__
#define __entity__

#include "stdafx.h"
#include "animation.h"

#define SPEED 200

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

		int currentDirection;
		int currentState;

		Animation *animation;
		void move(sf::Vector2i _direction);
		void setDirection(int _direction);
		void setState(int _state);

	public:
		Entity(const char *_path, sf::Vector2i _position);
		virtual ~Entity(){delete animation;}
		virtual void update(std::vector<sf::IntRect> collideRects);
		virtual void draw(sf::RenderWindow &window);
		virtual sf::Sprite getSprite();
};



#endif