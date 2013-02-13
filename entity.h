#ifndef __entity__
#define __entity__

#include <SFML/Graphics.hpp>
#include "animation.h"

#define SPEED 200

class Entity {
	protected:

		sf::Sprite sprite;
		sf::Clock eTime;
		sf::Time deltaTime;

		Animation *animation;
		void move(sf::Vector2i _direction);

	public:
		Entity(const char *_path, sf::Vector2i _position);
		virtual ~Entity(){}
		virtual void update();
		virtual void draw(sf::RenderWindow &window);
};



#endif