#ifndef __particle__
#define __particle__

#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

class Particle{
	private : 

		sf::Sprite sprite;

		sf::Texture texture;
		sf::Vector2f position;
		sf::Vector2f velocity;
		float angle;
		sf::Color color;
		int life;

	public : 

		Particle(sf::Texture texture, sf::Vector2f position, sf::Vector2f velocity, float angle, sf::Color color, int life);
		~Particle(){}

		void setTexture(sf::Texture texture);
		sf::Texture getTexture(){return texture;}

		void setPosition(sf::Vector2f position);
		sf::Vector2f getPosition(){return position;}

		void setVelocity(sf::Vector2f velocity);
		sf::Vector2f getVelocity(){return velocity;}

		void setAngle(float angle);
		float getAngle(){return angle;}

		void setColor(sf::Color color);
		sf::Color getColor(){return color;}

		void setLife(int life);
		int getLife(){return life;}

		void move();

		void update();
		void draw(sf::RenderWindow &window);

};

#endif __particle__