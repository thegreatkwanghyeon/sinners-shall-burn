#ifndef __skilleffectlist__
#define __skilleffectlist__

#include "particlesystem.h"
#include "skilleffect.h"

using namespace sf;

namespace skill{

	class FireBall : public SkillEffect{
		private : 
			float height;
			float scale;
			int fuel;
			ParticleSystem* fireballParticle;
		public : 
			FireBall();
			~FireBall(){
				delete fireballParticle;
			}

			virtual void update();
			virtual void draw(RenderWindow &window);

	};

	class Rain : public SkillEffect{
		private :
			ParticleSystem* cloud;
			ParticleSystem* rain;
		public : 
			Rain();
			~Rain(){
				delete cloud;
				delete rain;
			}
			
			virtual void update();
			virtual void draw(RenderWindow &window);
	};

}

#endif