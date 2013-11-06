#include "particlesystem.h"

namespace particle{
	class Water : public ParticleSystem{
		public : 

			Water(int x, int y);
			~Water(){}
			void initialize();
			virtual void setLocationList();
	};

	class FireBall : public ParticleSystem{
		public : 

			FireBall(int _x, int _y);
			~FireBall();
			void initialize();
			virtual void setLocationList();
			int x,y;
	};

	class Explosion : public ParticleSystem{
		public : 

			Explosion(int x, int y);
			~Explosion();
			void initialize();
			virtual void setLocationList();
	};
	class FireRain : public ParticleSystem{
		public : 

			FireRain(int x, int y);
			~FireRain();
			virtual void setLocationList();
			virtual void update();
			virtual void draw(sf::RenderWindow &window);

			FireBall* fireball[10];
	};
	class Rain : public ParticleSystem{
		public :
			Rain(int x, int y);
			~Rain();
			void initialize();
			virtual void setLocationList();
	};
}