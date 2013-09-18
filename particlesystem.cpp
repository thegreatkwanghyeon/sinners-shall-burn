#include "particlesystem.h"

ParticleSystem::ParticleSystem(int x, int y){
	m_position.x = x;
	m_position.y = y;
	m_particleSpeed = 300.0f;

	m_minLife = 50;
	m_maxLife = 100;

	m_minAngle = 0;
	m_maxAngle = 360;
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

void ParticleSystem::fuel(int num){
	Particle* particle;
	for(int i=0;i<num;i++){
		particle = new Particle();
		particle->sprite.setPosition(m_position.x, m_position.y);
		particle->vel.x = 0.5f;
		particle->vel.y = 0.5f;
		particle->life = m_randomizer.Next(m_minLife, m_maxLife);
		particle->angle = m_randomizer.Next(m_minAngle, m_maxAngle);

		m_particleList.push_back(particle);
	}
}

void ParticleSystem::update(){
	float time = m_clock.getElapsedTime().asSeconds();
	m_clock.restart();

	for(ParticleIterator it = m_particleList.begin(); it!=m_particleList.end(); it++){
		(*it)->life -= 1;
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