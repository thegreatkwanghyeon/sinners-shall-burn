#include "particlesystem.h"

ParticleSystem::ParticleSystem(int x, int y){
	m_position.x = x;
	m_position.y = y;
	m_particleSpeed = 300.0f;

	m_life = 50;
	m_lifeVar = m_life;

	m_angle = 0;
	m_angleVar = 360;

	m_velocity = 0.5;

	m_texturePath = "img/particles/star.png";

	m_startColor = sf::Color(0, 0, 0, 0);
	m_endColor = sf::Color(0, 0, 0, 0);
	m_startColorVar = sf::Color(0, 0, 0, 0);
	m_endColorVar = sf::Color(0, 0, 0, 0);

	m_elapsedTime = 0.0;
}

ParticleSystem::~ParticleSystem(){
	for( ParticleIterator it = m_particleList.begin(); it != m_particleList.end(); it++ )
	{
		delete *it;
	}
}

void ParticleSystem::setLocationVar(sf::Vector2i positionVar){
	m_positionVar = positionVar;
}

void ParticleSystem::setAngle(int angle){
	m_angle = angle;
	m_angleVar = m_angle;
}

void ParticleSystem::setAngleVar(int angleVar){
	m_angleVar = angleVar;
}

void ParticleSystem::setLife(int life){
	m_life = life;
	m_lifeVar = m_life;
}

void ParticleSystem::setLifeVar(int lifeVar){
	m_lifeVar = lifeVar;
}

void ParticleSystem::setStartColor(int r, int g, int b, int a){
	m_startColor = sf::Color(r, g, b, a);
	m_startColorVar = sf::Color(r, g, b, a);
}

void ParticleSystem::setEndColor(int r, int g, int b, int a){
	m_endColor = sf::Color(r, g, b, a);
	m_endColorVar = sf::Color(r, g, b, a);
}

void ParticleSystem::setStartColorVar(int r, int g, int b, int a){
	m_startColorVar = sf::Color(r, g, b, a);
}

void ParticleSystem::setEndColorVar(int r, int g, int b, int a){
	m_endColorVar = sf::Color(r, g, b, a);
}

void ParticleSystem::fuel(int num){
	Particle* particle;
	for(int i=0;i<num;i++){
		particle = new Particle(m_texturePath);
		particle->startvel = m_randomizer.NextFloat(m_velocity, m_velocityVar);
		particle->sprite.setPosition(m_randomizer.Next(m_position.x, m_positionVar.x), m_randomizer.Next(m_position.y, m_positionVar.y));
		particle->life = m_randomizer.Next(m_life, m_lifeVar);
		particle->defaultLife = particle->life;
		particle->angle = m_randomizer.Next(m_angle, m_angleVar);

		int r = m_randomizer.Next(m_startColor.r, m_startColorVar.r);
		int g = m_randomizer.Next(m_startColor.g, m_startColorVar.g);
		int b = m_randomizer.Next(m_startColor.b, m_startColorVar.b);
		int a = m_randomizer.Next(m_startColor.a, m_startColorVar.a);

		particle->startColor = sf::Color(r,g,b,a);

		r = m_randomizer.Next(m_endColor.r, m_endColorVar.r);
		g = m_randomizer.Next(m_endColor.g, m_endColorVar.g);
		b = m_randomizer.Next(m_endColor.b, m_endColorVar.b);
		a = m_randomizer.Next(m_endColor.a, m_endColorVar.a);

		particle->endColor = sf::Color(r,g,b,a);

		particle->sprite.setColor(particle->startColor);

		m_particleList.push_back(particle);
	}
}

void ParticleSystem::setSpeedVar(float speed){
	m_velocityVar = speed;
}

void ParticleSystem::fuelInSequence(float rate, int particles){
	m_elapsedTime += m_clock2.getElapsedTime().asSeconds();
	m_clock2.restart();

	if(m_elapsedTime >= rate){
		fuel(particles);
		m_elapsedTime = 0;
	}
}

void ParticleSystem::setSpeed(float speed){
	m_velocity = speed;
	m_velocityVar = m_velocity;
}

void ParticleSystem::setTexture(std::string texturePath){
	m_texturePath = texturePath;
}

void ParticleSystem::update(){
	float time = m_clock.getElapsedTime().asSeconds();
	m_clock.restart();

	for(ParticleIterator it = m_particleList.begin(); it!=m_particleList.end(); it++){
		(*it)->life -= 1;
		
		double lifeRatio = (double)(*it)->life/(double)(*it)->defaultLife;
		int r, g, b, a;

		r = (*it)->startColor.r * lifeRatio + (*it)->endColor.r * (1-lifeRatio);
		g = (*it)->startColor.g * lifeRatio + (*it)->endColor.g * (1-lifeRatio);
		b = (*it)->startColor.b * lifeRatio + (*it)->endColor.b * (1-lifeRatio);
		a = (*it)->startColor.a * lifeRatio + (*it)->endColor.a * (1-lifeRatio);

		(*it)->sprite.setColor(sf::Color(r, g, b, a));

		float velocity = (*it)->startvel * lifeRatio;

		(*it)->sprite.setPosition((*it)->sprite.getPosition().x + velocity * time * m_particleSpeed * cos((*it)->angle*M_PI/180), (*it)->sprite.getPosition().y + velocity * time * m_particleSpeed * -sin((*it)->angle*M_PI/180));
		if((*it)->life <= 0){
			delete (*it);
			it = m_particleList.erase( it );
			if( it == m_particleList.end() ) return;
		}
	}
}

void ParticleSystem::draw(sf::RenderWindow &window){
	for( ParticleIterator it = m_particleList.begin(); it != m_particleList.end(); it++ ){
			window.draw((*it)->sprite);
	}
}

void ParticleSystem::setLocation(sf::Vector2i position){
	m_position.x = position.x;
	m_position.y = position.y;

	m_positionVar = m_position;
}
void ParticleSystem::setLocationList(){
	return;
}