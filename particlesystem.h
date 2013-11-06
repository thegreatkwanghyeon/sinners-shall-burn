#ifndef __particlesystem__
#define __particlesystem__

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "well512.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Particle{
	public : 
		Particle(std::string texturePath){
			texture.loadFromFile(texturePath);
			sprite.setTexture(texture);
		}
		~Particle(){}
		sf::Texture texture;
		sf::Sprite sprite;
		float startvel;
		float vel;
		float angle;
		int life;
		int defaultLife;
		sf::Color endColor;
		sf::Color startColor;
};

typedef std::list<Particle*>::iterator ParticleIterator;

class ParticleSystem{
	private : 

		sf::Vector2i	m_position;
		sf::Vector2i m_positionVar;
		Well512	m_randomizer;
		sf::Clock	m_clock;
		sf::Clock m_clock2;

		float m_elapsedTime;

		float		m_particleSpeed;
		std::string m_texturePath;

		int m_angle, m_angleVar;
		int m_life, m_lifeVar;

		sf::Color m_startColor;
		sf::Color m_startColorVar;
		sf::Color m_endColor;
		sf::Color m_endColorVar;

		float m_velocity;
		float m_velocityVar;

	public :

		std::list<Particle*> m_particleList;

		ParticleSystem(int x, int y);
		~ParticleSystem();

		void fuel(int num);
		void fuelInSequence(float rate, int particles);

		void update();

		void draw(sf::RenderWindow &window);
		void setTexture(std::string texturePath);
		void setLocation(sf::Vector2i position);
		void setLocationVar(sf::Vector2i positionVar);
		void setLife(int life);
		void setLifeVar(int lifeVar);
		void setAngle(int angle);
		void setAngleVar(int angleVar);
		void setStartColor(int r, int g, int b, int a);
		void setStartColorVar(int r, int g, int b, int a);
		void setEndColor(int r, int g, int b, int a);
		void setEndColorVar(int r, int g, int b, int a);
		void setSpeed(float speed);
		void setSpeedVar(float speed);
		virtual void setLocationList();//ㅎㅎ내가 추가한 함수임. 오버라이딩용.
};

#endif