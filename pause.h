#ifndef __pause__
#define __pause__

#include "button.h"

class Pause{
	private:
		bool isPause,endFlag;
		Button* cButton;//��Ƽ��(�������� ���ư���)
		Button* endButton;//���� �����Ű��
	public:
		Pause();
		~Pause();
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);

		bool getState();
		bool isEnd();//�����ư �������� ���ӽſ��� ����, ������ ����
		void pauseOn();
		void pauseOff();
};

#endif