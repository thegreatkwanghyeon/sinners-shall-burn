#ifndef __particlelist__
#define __particlelist__

#include "particles.h"
#include "SFML/Audio.hpp"
#include "global.h"
#include "skill.h"
class ParticleList{
	private : 
		int num;
		int x,y;
		sf::SoundBuffer soundBuffer;
		sf::Sound sound;

		ParticleSystem *particle;
	public :

		ParticleList(int _x, int _y);
		~ParticleList();

		void setParticle(int _num, sf::String _path);
		void update();
		void draw(sf::RenderWindow &window);
		void setLocationList();
};

#endif