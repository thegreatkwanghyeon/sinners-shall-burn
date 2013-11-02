#ifndef __makemap__
#define __makemap__
#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MapX 25
#define MapY 25
#define DeathLimit 3
#define BirthLimit 4

class MakeMap{
	private:
		int map[MapY+1][MapX+1],oldmap[MapY+1][MapX+1];

		sf::Vector2i portal;

		void makeRandomMap();
		int countNeighbours(int x, int y);
		void makeDoor();
		bool isOpen(int _x, int _y);
		
		int maxLocPos;
		int chk[MapY+100][MapX+100];
	public:
		MakeMap();
		~MakeMap(){}
		void buildMap(int fNum);
		int getMap(int y, int x);
		sf::Vector2i getEnemyPos(int num, int max);

		sf::Vector2i getPortal();
};
#endif