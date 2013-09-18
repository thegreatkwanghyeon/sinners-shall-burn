#include "particlesystem.h"

ParticleSystem::ParticleSystem(int x, int y){
	m_position.x = x;
	m_position.y = y;
	m_particleSpeed = 300.0f;

	m_minLife = 50;
	m_maxLife = 100;

	m_minAngle = 0;
	m_maxAngle = 360;

	m_startColor = sf::Color(0, 0, 0, 0);
	m_endColor = sf::Color(0, 0, 0, 0);
}

ParticleSystem::~ParticleSystem(){
	for( ParticleIterator it = m_particleList.begin(); it != m_particleList.end(); it++ )
	{
		delete *it;
	}
}

void ParticleSystem::setAngleRange(int min, int max){
	m_minAngle = min;
	m_maxAngle = max;
}

void ParticleSystem::setLifeRange(int min, int max){
	m_minLife = min;
	m_maxLife = max;
}

void ParticleSystem::setStartColor(int r, int g, int b, int a){
	m_startColor = sf::Color(r, g, b, a);
}

void ParticleSystem::setEndColor(int r, int g, int b, int a){
	m_endColor = sf::Color(r, g, b, a);
}

void ParticleSystem::fuel(int num){
	Particle* particle;
	for(int i=0;i<num;i++){
		particle = new Particle();
		particle->sprite.setPosition(m_position.x, m_position.y);
		particle->vel.x = 0.5f;
		particle->vel.y = 0.5f;
		particle->life = m_randomizer.Next(m_minLife, m_maxLife);
		particle->defaultLife = particle->life;
		particle->angle = m_randomizer.Next(m_minAngle, m_maxAngle);
		particle->sprite.setColor(m_startColor);

		m_particleList.push_back(particle);
	}
}

void ParticleSystem::update(){
	float time = m_clock.getElapsedTime().asSeconds();
	m_clock.restart();

	for(ParticleIterator it = m_particleList.begin(); it!=m_particleList.end(); it++){
		(*it)->life -= 1;
		double lifeRatio = (double)(*it)->life/(double)(*it)->defaultLife * 100;
		int r, g, b, a;

		r = (m_endColor.r - m_startColor.r) * lifeRatio/100;
		g = (m_endColor.g - m_startColor.g) * lifeRatio/100;
		b = (m_endColor.b - m_startColor.b) * lifeRatio/100;
		a = (m_endColor.a - m_startColor.a) * lifeRatio/100;

		(*it)->sprite.setColor(sf::Color(r, g, b, a));
		(*it)->sprite.setPosition((*it)->sprite.getPosition().x + (*it)->vel.x * time * m_particleSpeed * cos((*it)->angle*M_PI/180), (*it)->sprite.getPosition().y + (*it)->vel.y * time * m_particleSpeed * -sin((*it)->angle*M_PI/180));
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

void ParticleSystem::setLocation(sf::Vector2f position){
	m_position.x = position.x;
	m_position.y = position.y;
}