#ifndef __skilleffectlist__
#define __skilleffectlist__

#include "particlesystem.h"
#include "lightning.h"
#include "skilleffect.h"

using namespace sf;

namespace skill{

	class FireBall : public SkillEffect{
		private : 
			ParticleSystem* fireballParticle;
			ParticleSystem* explosionParticle;
		public : 
			FireBall();
			~FireBall(){
				delete fireballParticle;
				delete explosionParticle;
			}

			virtual void update();
			virtual void draw(RenderWindow &window);

	};
}

#endif