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

		void makeRandomMap();
		int countNeighbours(int x, int y);
	public:
		MakeMap();
		~MakeMap(){}
		void buildMap();
		int getMap(int y, int x);
};
#endif