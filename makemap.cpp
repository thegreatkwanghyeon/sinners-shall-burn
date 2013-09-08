#include "makemap.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

MakeMap::MakeMap(){
	int i,j;
	for(i=0;i<MapY;i++){
		for(j=0;j<MapX;j++){
			oldmap[i][j]=map[i][j]=0;
		}
	}
}

void MakeMap::buildMap(){
	int i,j,k;
	int nbs;
	FILE *in = fopen("tile.txt","r");


	makeRandomMap();
	//--------------
	for(k=0;k<6;k++){
		for(i=0;i<MapY;i++){
			for(j=0;j<MapX;j++){
				nbs = countNeighbours(i,j);

				if(oldmap[i][j]){
					if(nbs < DeathLimit){
						map[i][j] = false;
					}
					else{
						map[i][j] = true;
					}
				}
				//반대로, 칸이 false 값이면, true 로바뀌기에 적당한 갯수의 true 인 이웃하는 칸이 있는지 체크합시다.
				else{
					if(nbs > BirthLimit){
						map[i][j] = true;
					}
					else{
						map[i][j] = false;
					}
				}
			}
		}
	}
	//-----
	for(i=0;i<MapY;i++){
		for(j=0;j<MapX;j++){
			fscanf(in,"%d",&k);
			if(k == 0)
				map[i][j]=0;
		}
	}
	fclose(in);

	//---
	for(i=0;i<MapY;i++){
		for(j=0;j<MapX;j++){
			if(i == 0 || j == 0 || j == MapX-1 || i == MapY-1)
				map[i][j]=true;
		}
	}
	
	for(i=0;i<MapY;i++){
		for(j=0;j<MapX;j++){
			if(map[i][j] == 1)
				printf("■");
			else
				printf("□");		
		}
		printf("\n");
	}
	printf("-=-=-=-=-=-=\n");
	//--------------
}
void MakeMap::makeRandomMap(){
	int i,j;
	int old=0,rd;
	int chanceToStartAlive = 50;
	srand(time(NULL));
	for(i=0; i<MapY; i++){
        for(j=0;j<MapX;j++){
			while(1){
				rd = rand()%100;
				if(rd != old){
					old=rd;
					break;
				}
			}
            if(rd < chanceToStartAlive)
                oldmap[i][j] = true;
            else
				oldmap[i][j]=false;
        }
    }
}
int MakeMap::countNeighbours(int x, int y){
    int count = 0;
    for(int i=-1; i<2; i++){
        for(int j=-1; j<2; j++){
            int neighbour_x = x+i;
            int neighbour_y = y+j;
            //검색할 칸에 있다면
            if(i == 0 && j == 0){
                //아무것도 안해요! 우리는 이웃하는 칸을 셀것입니다.
            }
            //만약에 우리가 검색할 칸이 맵의 테두리에 있다면
            else if(neighbour_x < 0 || neighbour_y < 0 || neighbour_x >= MapX || neighbour_y >= MapY){
                count = count + 1;
            }
            //그것도 아니면, 일반적으로 검색합니다
            else if(oldmap[neighbour_x][neighbour_y]){
                count = count + 1;
            }
        }
    }
	return count;
}
int MakeMap::getMap(int y, int x){
	return map[y][x];
}