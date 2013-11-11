#ifndef __particlesystem__
#define __particlesystem__

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "well512.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Particle{
	public : 
		Particle(sf::Texture &texture){
			sprite.setTexture(texture);
		}
		~Particle(){}
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
		sf::Texture m_texture;

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

		ParticleSystem();
		~ParticleSystem();

		void fuel(int num);
		void fuelInSequence(float rate, int particles);

		virtual void update();

		virtual void draw(sf::RenderWindow &window);
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


		float getSpeed(){return m_velocity;}
		float getSpeedVar(){return m_velocityVar;}
		sf::Vector2i getLocation(){return m_position;}
		sf::Vector2i getLocationVar(){return m_positionVar;}
		int getLife(){return m_life;}
		int getLifeVar(){return m_lifeVar;}
		int getAngle(){return m_angle;}
		int getAngleVar(){return m_angleVar;}
		sf::Color getStartColor(){return m_startColor;}
		sf::Color getStartColoVar(){return m_startColorVar;}
		sf::Color getEndColor(){return m_endColor;}
		sf::Color getEndColoVar(){ return m_endColorVar; }


		virtual void setLocationList();//ㅎㅎ내가 추가한 함수임. 오버라이딩용.
};

#endif