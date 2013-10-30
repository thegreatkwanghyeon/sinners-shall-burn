#ifndef __particlelist__
#define __particlelist__

#include "particles.h"
class ParticleList{
	private : 
		int num;
		int x,y;

		ParticleSystem *particle;
	public :

		ParticleList(int _x, int _y);
		~ParticleList();

		void setParticle(int _num);
		void update();
		void draw(sf::RenderWindow &window);
		void setLocationList();
};

#endif