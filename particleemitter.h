#ifndef __particleemitter__
#define __particleemitter__

#include "particle.h"
#include "windows.h"

class ParticleEmitter{
	private : 
		std::vector<Particle*> particlePool;
		Particle* getAFreeParticleFromThePool();
		void addParticle();
		bool shouldEmitSomeParticles(sf::Time deltaTime);

		int particleCount;
		float emissionRate;

		int minSpeed;
		int maxSpeed;
		int minSize;
		int maxSize;
		int minLife;
		int maxLife;
		int minAngle;
		int maxAngle;
		int minX, maxX;
		int minY, maxY;

		float tmpElapsedTime;
		sf::Time deltaTime;
		sf::Clock eTime;

		sf::Texture tmpTexture;

	public :

		ParticleEmitter(int numberOfParticles);
		~ParticleEmitter();

		void setEmissionRate(float emissionRate);
		void setSpeedRange(int min, int max);
		void setSizeRange(int min, int max);
		void setLifeRange(int min, int max);
		void setAngleRange(int min, int max);

		void setPositionRange(sf::Vector2i x, sf::Vector2i y);

		void setTexture(std::string string);

		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);

};

#endif __particleemitter__