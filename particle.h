#ifndef __particle__
#define __particle__


#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

class Particle : public sf::Sprite{
	private : 
		int life;
		int angle;
		int speed;
		int size;
		sf::Vector2f velocity;
		float radian;

		float tmpElapsedTime;
		sf::Time deltaTime;
		sf::Clock eTime;

		void move(float dt);

	public : 
		Particle();
		~Particle();

		void setTexture(sf::Texture texture);

		void setLife(int life);
		void setAngle(int angle);
		void setSpeed(int speed);
		void setSize(int size);

		float getLife();

		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);
};
#endif __particle__