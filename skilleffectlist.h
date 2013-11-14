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

	class Flood : public SkillEffect{
		private : 
			ParticleSystem* flood;
			float locationVarY;
			float temp;
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

	class Heal : public SkillEffect{
		private: 
			ParticleSystem* heal;
		public :
			Heal();
			~Heal(){
				delete heal;
			}

			virtual void update();
			virtual void draw(RenderWindow &window);

	};

	class Seed : public SkillEffect{
		private: ;
			ParticleSystem* heal;
			float alpha;
		public : 

			Seed();
			~Seed(){
				delete heal;
			}

			virtual void update();
			virtual void draw(RenderWindow &window);

	};


	class LightningBolt : public SkillEffect{
	private:
		ParticleSystem* cloud;
		Lightning* lightning;
		Well512* randomizer;
	public:

		LightningBolt();
		~LightningBolt(){
			delete lightning;
			delete cloud;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);

	};


	class ElectricShock : public SkillEffect{
	private:
		ParticleSystem* timer;
		Lightning* lightning;
		Well512* randomizer;
	public:

		ElectricShock();
		~ElectricShock(){
			delete timer;
			delete lightning;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);

	};

	class LightningStorm : public SkillEffect{
	private:
		ParticleSystem* cloud;
		Lightning* lightning;
		Well512* randomizer;
	public:

		LightningStorm();
		~LightningStorm(){
			delete lightning;
			delete cloud;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);

	};

	class Blizzard : public SkillEffect{
	private:
		ParticleSystem* cloud;
		ParticleSystem* snow;
	public:
		Blizzard();
		~Blizzard(){
			delete cloud;
			delete snow;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class IceShield : public SkillEffect{
	private:
		ParticleSystem* particleLeft, *particleRight;
	public:
		IceShield();
		~IceShield(){
			delete particleLeft;
			delete particleRight;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class AbsoluteZero : public SkillEffect{
	private:
		ParticleSystem* ice;
	public:
		AbsoluteZero();
		~AbsoluteZero(){
			delete ice;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};


	class FrozenSpear : public SkillEffect{
		private:
			Texture texture;
			Sprite spear;
			ParticleSystem* ice;
		public :
			FrozenSpear();
			~FrozenSpear(){
				delete ice;
			}

			virtual void update();
			virtual void draw(RenderWindow &window);

	};

	class EarthSplitter : public SkillEffect{
		private :
			ParticleSystem* particle;
		public : 

			EarthSplitter();
			~EarthSplitter(){
				delete particle;
			}
			virtual void update();
			virtual void draw(RenderWindow &window);
	};

	class SandStorm : public SkillEffect{
	private:
		ParticleSystem* sand;
	public:
		SandStorm();
		~SandStorm(){
			delete sand;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class EarthShake : public SkillEffect{
	private:
		ParticleSystem* particle;
	public:

		EarthShake();
		~EarthShake(){
			delete particle;
		}
		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class Gust : public SkillEffect{
	private:
		ParticleSystem* sand;
	public:
		Gust();
		~Gust(){
			delete sand;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class SonicBoom : public SkillEffect{
	private:
		ParticleSystem* sand;
	public:
		SonicBoom();
		~SonicBoom(){
			delete sand;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class Steam : public SkillEffect{
	private:
		ParticleSystem* sand;
	public:
		Steam();
		~Steam(){
			delete sand;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class HotWater : public SkillEffect{
	private:
		ParticleSystem* sand;
	public:
		HotWater();
		~HotWater(){
			delete sand;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class StormyRain : public SkillEffect{
	private:
		ParticleSystem* cloud;
		ParticleSystem* rain;
		ParticleSystem* storm;
	public:
		StormyRain();
		~StormyRain(){
			delete cloud;
			delete rain;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class Hail : public SkillEffect{
	private:
		ParticleSystem* cloud;
		ParticleSystem* rain;
	public:
		Hail();
		~Hail(){
			delete cloud;
			delete rain;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class Magma : public SkillEffect{
	private:
		ParticleSystem* flood;
		float locationVarY;
		int temp;
	public:
		Magma();
		~Magma(){
			delete flood;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class Poison : public SkillEffect{
	private:
		ParticleSystem* sand;
	public:
		Poison();
		~Poison(){
			delete sand;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class FatalPoison : public SkillEffect{
	private:
		ParticleSystem* sand;
	public:
		FatalPoison();
		~FatalPoison(){
			delete sand;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class Mud : public SkillEffect{
	private:
		float scale;
		ParticleSystem* fire;
	public:
		Mud();
		~Mud(){
			delete fire;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);

	};

	class MuddyWater : public SkillEffect{
	private:
		ParticleSystem* sand;
	public:
		MuddyWater();
		~MuddyWater(){
			delete sand;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class MuddyShield : public SkillEffect{
	private:
		ParticleSystem* particleLeft;
		ParticleSystem* particleRight;
	public:
		MuddyShield();
		~MuddyShield(){
			delete particleLeft;
			delete particleRight;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class LandSlides : public SkillEffect{
	private:
		ParticleSystem* snow;
	public:
		LandSlides();
		~LandSlides(){
			delete snow;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class SolarBeam : public SkillEffect{
	private:
		ParticleSystem* sand;
	public:
		SolarBeam();
		~SolarBeam(){
			delete sand;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class MagneticField : public SkillEffect{
	private:
		ParticleSystem* particle;
	public:
		MagneticField();
		~MagneticField(){
			delete particle;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class ChainOfEarth : public SkillEffect{
	private:
		ParticleSystem* particleLeft;
		ParticleSystem* particleRight;
	public:
		ChainOfEarth();
		~ChainOfEarth(){
			delete particleLeft;
			delete particleRight;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class Photosynthesis : public SkillEffect{
	private:
		ParticleSystem* heal;
		float alpha;
	public:

		Photosynthesis();
		~Photosynthesis(){
			delete heal;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);

	};

	class Meteor : public SkillEffect{
	private :
		ParticleSystem* meteor[5];
		Well512* randomizer;
	public : 
		Meteor();
		~Meteor(){
			delete randomizer;
			for (int i = 0; i < 5;i++)
				delete meteor[i];
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class Miss : public SkillEffect{
	private:

	public:

		Miss();
		~Miss(){
			
		}

		virtual void update();
		virtual void draw(RenderWindow &window);

	};

	class Frost : public SkillEffect{
	private:
		ParticleSystem* sand;
	public:
		Frost();
		~Frost(){
			delete sand;
		}

		virtual void update();
		virtual void draw(RenderWindow &window);
	};

	class Vaccum : public SkillEffect{
	private : 
		ParticleSystem* air;
		int x, y, xv, yv;
	public : 
		Vaccum();
		~Vaccum();
		virtual void update();
		virtual void draw(RenderWindow &window);
	};

}

#endif