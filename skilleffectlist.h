#ifndef __skilleffectlist__
#define __skilleffectlist__

#include "particlesystem.h"
#include "lightning.h"
#include "skilleffect.h"

using namespace sf;

namespace skill{

	class FireBall : public SkillEffect{
	private:
		ParticleSystem* fireParticle;
	public:
		FireBall();
		~FireBall(){
			delete fireParticle;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);

	};

	class DragonSlave : public SkillEffect{
		private : 
			float scale;
			ParticleSystem* fire;
		public : 
			DragonSlave();
			~DragonSlave(){
				delete fire;
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

	class WorldFire : public SkillEffect{
	private:

		int fuel;
		float locationVarX;

		float lifeTime;

		ParticleSystem* smoke;
		ParticleSystem* fire;
	public:
		WorldFire();
		~WorldFire(){
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

	class Flood : public SkillEffect{
		private : 
			ParticleSystem* flood;
			float locationVarY;
		public :	
			Flood();
			~Flood(){
				delete flood;
			}

			virtual void update();
			virtual void draw(RenderWindow &window);
	};

	class Trident : public SkillEffect{
		private	:
			ParticleSystem* water;
			ParticleSystem* waterPillar;
			Texture tridentTexture;
			Sprite trident;

			float move;
			float locationY;
		public : 

			Trident();
			~Trident(){
				delete water;
				delete waterPillar;
			}

			virtual void update();
			virtual void draw(RenderWindow &window);

	};

	class Tsunami : public SkillEffect{
		private : 
			ParticleSystem* tsunami;
			float locationVarY;
		public :

			Tsunami();
			~Tsunami(){
				delete tsunami;
			}

			virtual void update();
			virtual void draw(RenderWindow &window);
	};

}

#endif