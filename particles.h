#include "particlesystem.h"

namespace particle{
	class Water : public ParticleSystem{
		private :
			sf::Vector2i pos;
			//여기부턴 이동시 쓰는 변수들
			sf::Vector2i temp;//원래 위치값이 아닌 현재 위치값(current)
			sf::Clock delta;//시간

			sf::Vector2i move;//움직일 정도(init함수에서 받아옴)
			void setMove();//움직여줌
		public : 
			Water(int _x, int _y);
			~Water(){}
			void initialize(sf::Vector2i _move);//안움직일거면 인자 필요없음
			virtual void setLocationList();
	};

	class FireBall : public ParticleSystem{
		private :
			sf::Vector2i pos;
			sf::Vector2i temp;
			sf::Clock delta;
			
			sf::Vector2i move;
			void setMove();
		public : 
			FireBall(int _x, int _y);
			~FireBall();
			void initialize(sf::Vector2i _move);
			virtual void setLocationList();
	};

	class Explosion : public ParticleSystem{
		private :
			sf::Vector2i pos;
		public : 
			Explosion(int _x, int _y);
			~Explosion();
			void initialize();
			virtual void setLocationList();
	};
	class FireRain : public ParticleSystem{
		private :
			sf::Vector2i pos;
		public : 
			FireRain(int _x, int _y);
			~FireRain();
			virtual void setLocationList();
			virtual void update();
			virtual void draw(sf::RenderWindow &window);

			FireBall* fireball[7];
	};
	class Rain : public ParticleSystem{
		private :
			sf::Vector2i pos;
		public :
			Rain(int _x, int _y);
			~Rain();
			void initialize();
			virtual void setLocationList();
	};
	class Cut : public ParticleSystem{
		private :
			sf::Vector2i pos;
			sf::Vector2i temp;
			sf::Clock delta;
			
			sf::Vector2i move;
			void setMove();
		public : 
			Cut(int _x, int _y);
			~Cut();
			void initialize(sf::Vector2i _move);
			virtual void setLocationList();
	};
}