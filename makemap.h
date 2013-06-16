#ifndef __makemap__
#define __makemap__
#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MapX 20
#define MapY 20
#define Tile 5

class MakeMap{
	private:
		int map[MapY+100][MapX+100];
		int road[MapY+100][MapX+100];
		int tile[30][Tile+1][Tile+1];
		int old;

		bool chkMap();
		void buildMap();
		void findRoad(int x, int y);
	public:
		MakeMap();
		~MakeMap(){}
		int getMap(int y, int x);
};
#endif

	