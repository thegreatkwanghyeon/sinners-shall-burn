#ifndef __enemy__
#define __enemy__

#include "stdafx.h"
#include "tinyxml.h"
#include "global.h"

class Enemy{
	private:
		sf::Sprite sprite;
		sf::String name;
		int code;
		int maxHp;
		int currentHp;
		sf::Vector2f position;

		TiXmlDocument enemyData;

	public:
		Enemy();
		Enemy(int code);
		~Enemy();

		sf::String getName();
		int getMaxHp();
		int getCurrentHp();
		sf::Vector2f getPosition();
		sf::Sprite getSprite();

		
};

#endif