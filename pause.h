#ifndef __pause__
#define __pause__

#include "button.h"

class Pause{
	private:
		bool isPause,endFlag,titleFlag;
		Button* cButton;//콘티뉴(게임으로 돌아가기)
		Button* endButton;//게임 종료시키기
		Button* tButton;//타이틀로 가는 버튼
	public:
		Pause();
		~Pause();
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);

		bool getState();
		bool isEnd();//엔드버튼 눌렀을시 게임신에서 연동, 게임을 종료
		bool isGoTitle();
		void pauseOn();
		void pauseOff();
};

#endif