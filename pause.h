#ifndef __pause__
#define __pause__

#include "button.h"
#include "slider.h"

class Pause{
	private:
		bool isPause,endFlag,titleFlag;
		Button* cButton;//��Ƽ��(�������� ���ư���)
		Button* endButton;//���� �����Ű��
		Button* tButton;//Ÿ��Ʋ�� ���� ��ư
		Slider* slider;
	public:
		Pause();
		~Pause();
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);

		bool getState();
		bool isEnd();//�����ư �������� ���ӽſ��� ����, ������ ����
		bool isGoTitle();
		void pauseOn();
		void pauseOff();
};

#endif