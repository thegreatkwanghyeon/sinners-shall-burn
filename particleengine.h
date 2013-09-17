#ifndef __particleengine__
#define __particleengine__

#include <SFML/Graphics.hpp>
#include "particle.h"
#include <windows.h>

class ParticleEngine{
	private : 

		std::vector<sf::Texture> textureList;
		std::vector<Particle*> particleList;
		sf::Vector2f location;

		int numberOfParticles;
		unsigned int randomNumber;
	
	public : 

		ParticleEngine(std::vector<sf::Texture> textureList, int numberOfParticles);
		~ParticleEngine(){}

		Particle* generateNewParticle();

		void setLocation(sf::Vector2f location);
		void init();

		void update();
		void draw(sf::RenderWindow &window);

};

#endif __particleengine__