#ifndef __particlelist__
#define __particlelist__


#include "SFML/Audio.hpp"
#include "global.h"
#include "skill.h"
#include "skilleffectlist.h"

class ParticleList{
	private : 
		int num;
		int x,y;
		sf::SoundBuffer soundBuffer;
		sf::Sound sound;

		SkillEffect *skillEffect;
	public :

		ParticleList(int _x, int _y);
		~ParticleList();

		void setParticle(int _num, sf::String _path, bool isSound);
		void update();
		void draw(sf::RenderWindow &window);
		bool isEnd(){return skillEffect->isEnd();}
};

#endif