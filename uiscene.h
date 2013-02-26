#ifndef __uiscene__
#define __uiscene__

#include "scenebase.h"
#include "button.h"
#include "gauge.h"
#include "tooltip.h"



class UiScene : public SceneBase {

	private:
		Button *button;
		Button *button2;
		Gauge *gauge;
		Gauge *gauge2;
		Tooltip *tooltip;


	public:
		UiScene();
		virtual ~UiScene(){delete button; delete button2; delete gauge; delete gauge2; delete tooltip;}
		virtual void update();
		virtual void draw(sf::RenderWindow &window);

};

#endif