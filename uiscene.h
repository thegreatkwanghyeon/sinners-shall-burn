#ifndef __uiscene__
#define __uiscene__

#include "scenebase.h"
#include "button.h"
#include "gauge.h"
#include "tooltip.h"

#include <cstdio>

class UiScene : public SceneBase {

	private:
		Button *button;
		Button *button2;
		Gauge *gauge;
		Gauge *gauge2;
		Tooltip *tooltip;


	public:
		UiScene();
		~UiScene(){delete button; delete button2; delete gauge; delete gauge2;}
		void update();
		void draw(sf::RenderWindow &window);

};

#endif