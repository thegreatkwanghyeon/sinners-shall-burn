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
				//�ݴ��, ĭ�� false ���̸�, true �ιٲ�⿡ ������ ������ true �� �̿��ϴ� ĭ�� �ִ��� üũ�սô�.
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
				printf("��");
			else
				printf("��");		
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
            //�˻��� ĭ�� �ִٸ�
            if(i == 0 && j == 0){
                //�ƹ��͵� ���ؿ�! �츮�� �̿��ϴ� ĭ�� �����Դϴ�.
            }
            //���࿡ �츮�� �˻��� ĭ�� ���� �׵θ��� �ִٸ�
            else if(neighbour_x < 0 || neighbour_y < 0 || neighbour_x >= MapX || neighbour_y >= MapY){
                count = count + 1;
            }
            //�װ͵� �ƴϸ�, �Ϲ������� �˻��մϴ�
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