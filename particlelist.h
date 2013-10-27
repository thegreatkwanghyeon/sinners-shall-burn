#ifndef __particlelist__
#define __particlelist__

#include "particlesystem.h"
class ParticleList{
	private : 
		int num;
	public :
		ParticleSystem* particle;

		ParticleList(int x, int y);
		~ParticleList();

		void setParticle(int _num);
		void update();
		void draw(sf::RenderWindow &window);
		void setLocationList();
};

#endif