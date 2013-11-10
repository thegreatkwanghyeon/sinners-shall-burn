#ifndef __skilleffect__
#define __skilleffect__

#include "stdafx.h"

class SkillEffect{
	private : 
		bool end;
	public :
		SkillEffect();
		~SkillEffect();

		virtual void update();
		virtual void draw(sf::RenderWindow &window);

		void setEnd();

		bool isEnd(){return end;}
};

#endif