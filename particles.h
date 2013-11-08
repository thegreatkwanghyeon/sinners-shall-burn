#include "particlesystem.h"

namespace particle{
	class Water : public ParticleSystem{
		private :
			sf::Vector2i pos;
			//������� �̵��� ���� ������
			sf::Vector2i temp;//���� ��ġ���� �ƴ� ���� ��ġ��(current)
			sf::Clock delta;//�ð�

			sf::Vector2i move;//������ ����(init�Լ����� �޾ƿ�)
			void setMove();//��������
		public : 
			Water(int _x, int _y);
			~Water(){}
			void initialize(sf::Vector2i _move);//�ȿ����ϰŸ� ���� �ʿ����
			virtual void setLocationList();
	};
	class Fire : public ParticleSystem{
		private :
			sf::Vector2i pos;
		public :
			Fire(int _x, int _y);
			~Fire();
			void initialize();
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
	class FireRain2 : public ParticleSystem{
		private :
			sf::Vector2i pos;
		public : 
			FireRain2(int _x, int _y);
			~FireRain2();
			virtual void setLocationList();
			virtual void update();
			virtual void draw(sf::RenderWindow &window);

			Fire* fire[5];
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
	class Heal : public ParticleSystem{
		private :
			sf::Vector2i pos;
		public :
			Heal(int _x, int _y);
			~Heal();
			void initialize();
			virtual void setLocationList();
	};
	class Heal2 : public ParticleSystem{
		private :
			sf::Vector2i pos;
		public :
			Heal2(int _x, int _y);
			~Heal2();
			void initialize();
			virtual void setLocationList();
	};
	class Drain : public ParticleSystem{
		private :
			sf::Vector2i pos;
			sf::Vector2i temp;
			sf::Clock delta;
			
			sf::Vector2i move;
			void setMove();
		public : 
			Drain(int _x, int _y);
			~Drain();
			void initialize(sf::Vector2i _move);
			virtual void setLocationList();
	};
	class IceShield : public ParticleSystem{
		private :
			sf::Vector2i pos;
		public :
			IceShield(int _x, int _y);
			~IceShield();
			void initialize();
			virtual void setLocationList();
	};
	class Beam : public ParticleSystem{
		private :
			sf::Vector2i pos;
			sf::Vector2i temp;
			sf::Clock delta;
			
			sf::Vector2i move;
			void setMove();
		public : 
			Beam(int _x, int _y);
			~Beam();
			void initialize(sf::Vector2i _move);
			virtual void setLocationList();
	};
}