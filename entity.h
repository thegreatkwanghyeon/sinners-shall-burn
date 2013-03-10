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
		sf::Sprite collisionCheckSprite;

		int currentDirection;
		int currentState;

		Animation *animation;
		void move(sf::Vector2f _direction);
		void setDirection(int _direction);
		void setState(int _state);
		bool isCollision(sf::Vector2f _direction, std::vector<sf::FloatRect> collideRects);

	public:
		Entity(const char *_path, sf::Vector2i _position);
		virtual ~Entity(){delete animation;}
		virtual void update(std::vector<sf::FloatRect> collideRects);
		virtual void draw(sf::RenderWindow &window);
		virtual sf::Sprite getSprite();
};



#endif