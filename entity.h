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

		struct Margin{
			float top, left, bottom, right;
		}margin;

		sf::Sprite sprite;
		sf::Clock eTime;
		sf::Time deltaTime;
		sf::Sprite collisionCheckSprite;
		sf::FloatRect collisionBox;

		int currentDirection;
		int currentState;

		Animation *animation;
		void move(sf::Vector2f _direction);
		void setDirection(int _direction);
		void setState(int _state);
		void setCollisionBoxMargin(float top, float left, float bottom, float right);
		bool isCollision(sf::Vector2f _direction, std::vector<sf::FloatRect> collideRects);

	public:
		Entity(const char *_path, sf::Vector2i _position);
		virtual ~Entity(){delete animation;}
		virtual void update(std::vector<sf::FloatRect> collideRects);
		virtual void draw(sf::RenderWindow &window);
		virtual sf::Sprite getSprite();
};



#endif