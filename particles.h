#include "particlesystem.h"

namespace particle{
	class Water : public ParticleSystem{
		public : 

			Water(int x, int y);
			~Water(){}
			void initialize();

	};

	class Fire : public ParticleSystem{
		public : 

			Fire(int x, int y);
			~Fire();
			void initialize();

	};

	class Explosion : public ParticleSystem{
		public : 

			Explosion(int x, int y);
			~Explosion();
			void initialize();

	};
	class Rain : public ParticleSystem{
		public :
			Rain(int x, int y);
			~Rain();
			void initialize();
	};
}