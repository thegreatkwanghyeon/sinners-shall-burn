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
		float startVel;
		float endVel;

		sf::Vector2f startPosition;

		float startScale;
		float endScale;

		float angle;
		int life;
		int defaultLife;
		sf::Color endColor;
		sf::Color startColor;
};

typedef std::list<Particle*>::iterator ParticleIterator;

class ParticleSystem{
private:

	float scale;

	bool canFuel;

	float m_lifeTime;

	float m_startScale;
	float m_startScaleVar;

	float m_endScale;
	float m_endScaleVar;

	sf::Vector2f	m_position;
	sf::Vector2f m_positionVar;

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

	float m_startVelocity;
	float m_startVelocityVar;

	float m_endVelocity;
	float m_endVelocityVar;

	float m_rotation;
	float m_rotationVar;

public:

	std::list<Particle*> m_particleList;

	ParticleSystem();
	~ParticleSystem();

	void fuel(int num);
	void fuelInSequence(float rate, int particles);
	void fuelOnce(int num);

	virtual void update();

	virtual void draw(sf::RenderWindow &window);
	void setTexture(std::string texturePath);
	void setLocation(sf::Vector2f position);
	void setLocationVar(sf::Vector2f positionVar);
	void setLife(int life);
	void setLifeVar(int lifeVar);
	void setAngle(int angle);
	void setAngleVar(int angleVar);
	void setStartColor(int r, int g, int b, int a);
	void setStartColorVar(int r, int g, int b, int a);
	void setEndColor(int r, int g, int b, int a);
	void setEndColorVar(int r, int g, int b, int a);

	void setStartSpeed(float speed);
	void setStartSpeedVar(float speed);

	void setEndSpeed(float speed);
	void setEndSpeedVar(float speed);

	void setStartScale(float scale);
	void setStartScaleVar(float scale);
	void setEndScale(float scale);
	void setEndScaleVar(float scale);

	void setRotation(float rot);
	void setRotationVar(float rot);


	float getStartSpeed(){ return m_startVelocity; }
	float getStartSpeedVar(){ return m_startVelocityVar; }
	float getEndSpeed(){ return m_endVelocity; }
	float getEndSpeedVar(){ return m_endVelocityVar; }
	sf::Vector2f getLocation(){ return m_position; }
	sf::Vector2f getLocationVar(){ return m_positionVar; }
	int getLife(){ return m_life; }
	int getLifeVar(){ return m_lifeVar; }
	int getAngle(){ return m_angle; }
	int getAngleVar(){ return m_angleVar; }
	sf::Color getStartColor(){ return m_startColor; }
	sf::Color getStartColoVar(){ return m_startColorVar; }
	sf::Color getEndColor(){ return m_endColor; }
	sf::Color getEndColoVar(){ return m_endColorVar; }
	float getStartScale(){ return m_startScale; }
	float getStartScaleVar(){ return m_startScaleVar; }
	float getEndScale(){ return m_endScale; }
	float getEndScaleVar(){ return m_endScaleVar; }
	int getNumberOfParticle(){ return m_particleList.size(); }
	float getLifeTime(){ return m_lifeTime; }
	float getRatation(){ return m_rotation; }
	float getRotationVar(){ return m_rotationVar; }
};

#endif