#ifndef __particlesystem__
#define __particlesystem__

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "well512.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Particle{
	public : 
		Particle(){
			texture.loadFromFile("img/particles/star.png");
			sprite.setTexture(texture);
		}
		~Particle(){}
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Vector2f vel;
		int life;
		int defaultLife;
		float angle;
};

typedef std::list<Particle*>::iterator ParticleIterator;

class ParticleSystem{
	private : 

		sf::Vector2f	m_position;
		Well512	m_randomizer;
		sf::Clock	m_clock;
		float		m_particleSpeed;

		int m_minAngle, m_maxAngle;
		int m_minLife, m_maxLife;

		sf::Color m_startColor;
		sf::Color m_endColor;

		float m_startScale;
		float m_endScale;		

	public :

		std::list<Particle*> m_particleList;

		ParticleSystem(int x, int y);
		~ParticleSystem();

		void fuel(int num);
		void update();
		void draw(sf::RenderWindow &window);
		void setLocation(sf::Vector2f position);
		void setLifeRange(int min, int max);
		void setAngleRange(int min, int max);
		void setStartColor(int r, int g, int b, int a);
		void setEndColor(int r, int g, int b, int a);
};

#endif