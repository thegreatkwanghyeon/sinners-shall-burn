#include "particlesystem.h"
#include "lightning.h"

class SkillEffect{
	private : 
		list<ParticleSystem*> particleList;
		list<Lightning*> lightningList;
	public :
		SkillEffect(){}
		~SkillEffect();

		void update();
		void draw(RenderWindow &window);

		void addParticle(ParticleSystem* particle);
		void addLightning(Lightning* lightning);
};