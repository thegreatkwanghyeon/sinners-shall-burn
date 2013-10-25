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

void MakeMap::buildMap(int fNum){
	int i,j,k;
	int nbs;


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
	for(i=1;i<MapY-1;i++){
		for(j=1;j<MapX-1;j++){
			if(/*i == 2 || i == MapY-3 || */i == (int)(MapY/2) || j == 2 || j == MapX-3 || j == (int)(MapX/2))//��� ���ε�
				map[i][j]=0;
			else if((i <= 3 && j >= MapY-4) || (i >= MapY-4 && j <= 3))
				map[i][j]=0;
		}
	}

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
	makeDoor();
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
void MakeMap::makeDoor(){//BFS �˰��� ���.
	int s=0,e=1;
	int maxLoc,max=1;
	sf::Vector2i stack[MapX*MapY+100];//�����Ӱ�~
	int chk[MapY+100][MapX+100];
	//---

	for(int i=0;i<MapY;i++){
		for(int j=0;j<MapX;j++){
			chk[i][j]=0;
		}
	}

	//stack[s].x=2;
	//stack[s].y=2;
	stack[s].x=2;
	stack[s].y=2;
	chk[stack[s].y][stack[s].x]=1;//���۰��� 1��.
	//�ϴ� ���۰��� �߾�(��ĭ). �߾����κ��� �����ؼ� ���� ���� ĭ�� ���� ��ġ�Ѵ�.
	while(1){
		if(s>e)
			break;
		if(stack[s].y-1 > 0 && chk[stack[s].y-1][stack[s].x] == 0 && map[stack[s].y-1][stack[s].x] == 0){//���� ���� ���. 0�� �ܺ��̶� �ȵ�.
			chk[stack[s].y-1][stack[s].x] = chk[stack[s].y][stack[s].x]+1;
			if(max < chk[stack[s].y-1][stack[s].x]){
				max=chk[stack[s].y-1][stack[s].x];
				maxLoc=e;
			}
			stack[e].x=stack[s].x;
			stack[e].y=stack[s].y-1;
			e++;
		}
		if(stack[s].y+1 < MapY-1 && chk[stack[s].y+1][stack[s].x] == 0 && map[stack[s].y+1][stack[s].x] == 0){//�Ʒ��� ���� ���.
			chk[stack[s].y+1][stack[s].x] = chk[stack[s].y][stack[s].x]+1;
			if(max < chk[stack[s].y+1][stack[s].x]){
				max=chk[stack[s].y+1][stack[s].x];
				maxLoc=e;
			}
			stack[e].x=stack[s].x;
			stack[e].y=stack[s].y+1;
			e++;
		}
		if(stack[s].x-1 > 0 && chk[stack[s].y][stack[s].x-1] == 0 && map[stack[s].y][stack[s].x-1] == 0){//�������� ���� ���.
			chk[stack[s].y][stack[s].x-1] = chk[stack[s].y][stack[s].x]+1;
			if(max < chk[stack[s].y][stack[s].x-1]){
				max=chk[stack[s].y][stack[s].x-1];
				maxLoc=e;
			}
			stack[e].x=stack[s].x-1;
			stack[e].y=stack[s].y;
			e++;
		}
		if(stack[s].x+1 < MapX-1 && chk[stack[s].y][stack[s].x+1] == 0 && map[stack[s].y][stack[s].x+1] == 0){//���������� ���� ���.
			chk[stack[s].y][stack[s].x+1] = chk[stack[s].y][stack[s].x]+1;
			if(max < chk[stack[s].y][stack[s].x+1]){
				max=chk[stack[s].y][stack[s].x+1];
				maxLoc=e;
			}
			stack[e].x=stack[s].x+1;
			stack[e].y=stack[s].y;
			e++;
		}
		s++;
	}
	for(int i=0;i<MapY;i++){
		for(int j=0;j<MapX;j++){
			printf("%2d ",chk[i][j]);
		}
		printf("\n");
	}
	map[stack[maxLoc].y][stack[maxLoc].x]=9;//��¦
	portal=stack[maxLoc];
}
sf::Vector2i MakeMap::getPortal(){
	return portal;
}