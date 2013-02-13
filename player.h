#ifndef __player__
#define __player__

#include "entity.h"

class Player : public Entity {
	private:

	public:
		Player(const char *_path , sf::Vector2i _position);
		virtual ~Player(){}

		virtual void update();
		virtual void draw(sf::RenderWindow &window);
};

#endif