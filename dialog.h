#ifndef __dialog__
#define __dialog__

#include "windowentity.h"

class Dialog : public WindowEntity {
	private:


	public:
		Dialog(const char *_path);
		virtual ~Dialog(){}
		virtual void update();
		virtual void draw(sf::RenderWindow &window);


};



#endif