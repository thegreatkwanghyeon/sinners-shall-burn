#ifndef __skilleffectlist__
#define __skilleffectlist__

#include "particlesystem.h"
#include "lightning.h"
#include "skilleffect.h"

using namespace sf;

namespace skill{

	class FireBall : public SkillEffect{
	private:
		ParticleSystem* explosionParticle;
	public:
		FireBall();
		~FireBall(){
			delete explosionParticle;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);

	};


	class HellFire : public SkillEffect{
		private : 

			int fuel;
			float locationVarX;

			float lifeTime;

			ParticleSystem* smoke;
			ParticleSystem* fire;
		public : 
			HellFire();
			~HellFire(){
				delete fire;
				delete smoke;
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

	class LightningBolt : public SkillEffect{
		private : 
			ParticleSystem* cloud;
			Lightning* lightning;
			Well512* randomizer;
		public :

			LightningBolt();
			~LightningBolt(){
				delete lightning;
			}

			virtual void update();
			virtual void draw(RenderWindow &window);

	};

}

#endif