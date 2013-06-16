#include "makemap.h"

MakeMap::MakeMap(){
	int i,j;
	old=-1;

	for(i=0;i<MapY/Tile;i++){
		for(j=0;j<MapX/Tile;j++){
			road[i][j]=0;
		}
	}

	buildMap();
}

bool MakeMap::chkMap(){
	int i,j;
	for(i=0;i<MapY/Tile;i++){
		for(j=0;j<MapX/Tile;j++){
			if(road[i][j] == 0)
				return false;
		}
	}
	return true;
}
void MakeMap::findRoad(int x, int y){
	int loc;
	int cnt=0;

    srand(time(NULL));

	while(1){
		cnt++;
		if(cnt >= 100)
			old=-1;
		while(1){
			loc=rand()%4;
			if(old != loc)
				break;
		}
		//printf("%d\n",rand());
		if(y > 0 && road[y-1][x] == 0 && loc == 0){//위
			road[y-1][x]+=4;
			road[y][x]+=1;
			old=loc;
			findRoad(x,y-1);
		}else if(x+1 < MapX/Tile && road[y][x+1] == 0 && loc == 1){//오른쪽
			road[y][x+1]+=8;
			road[y][x]+=2;
			old=loc;
			findRoad(x+1,y);
		}else if(y+1 < MapY/Tile && road[y+1][x] == 0 && loc == 2){//아래
			road[y+1][x]+=1;
			road[y][x]+=4;
			old=loc;
			findRoad(x,y+1);
		}else if(x > 0 && road[y][x-1] == 0 && loc == 3){//왼쪽
			road[y][x-1]+=2;
			road[y][x]+=8;
			old=loc;
			findRoad(x-1,y);
		}
		if(road[y][x] == 15 || chkMap() == true || ((y == 0 || road[y-1][x] != 0) && (y+1 == MapY/Tile || road[y+1][x] != 0) && (x == 0 || road[y][x-1] != 0) && (x+1 == MapX/Tile || road[y][x+1]) != 0))
			break;
	}
}

void MakeMap::buildMap(){
	int i,j,k,l;
	FILE *in = fopen("tile.txt","r");

	for(i=0;i<16;i++){
		for(j=0;j<Tile;j++){
			for(k=0;k<Tile;k++){
				fscanf(in,"%d",&tile[i][j][k]);
			}
		}
	}
	fclose(in);

	findRoad(0,0);
	/*
	srand(time(NULL));
	for(i=0;i<10;i++){
		rdx=rand()%10;
		while(1){
			rdy=rand()%10;
			if(rdy != rdx)
				break;
		}
		if(road[rdy][rdx] == 15){
			i--;
			continue;
		}else{
			temp=road[rdy][rdx];
			for(j=0;j<4;j++){
				check[j]=temp%2;
				temp /= 2;
			}
			printf("변경 : %d %d!%d[%d %d %d %d]-flag %d\n",rdx,rdy,road[rdy][rdx],road[rdy][rdx]&1,road[rdy][rdx]&2,road[rdy][rdx]&4,road[rdy][rdx]&8,road[rdy][rdx]&1==0);
			if(rdy != 0 && check[0] == 0){
				road[rdy][rdx]+=1;
				road[rdy-1][rdx]+=4;
			}
			if(rdy != 9 && check[1] == 0){
				road[rdy][rdx]+=2;
				road[rdy][rdx+1]+=8;
			}
			if(rdy != 9 && check[2] == 0){
				road[rdy][rdx]+=4;
				road[rdy+1][rdx]+=1;
			}
			if(rdy != 0 && check[3] == 0){
				road[rdy][rdx]+=8;
				road[rdy][rdx-1]+=2;
			}
			printf("변경 : %d %d!%d[%d %d %d %d]\n",rdx,rdy,road[rdy][rdx],road[rdy][rdx]&1,road[rdy][rdx]&2,road[rdy][rdx]&4,road[rdy][rdx]&8);
		}
	}*/

	for(i=0;i<MapY/Tile;i++){
		for(j=0;j<MapX/Tile;j++){
			for(k=0;k<Tile;k++){
				for(l=0;l<Tile;l++){
					//printf("%d %d [%d %d %d %d] %d\n",i*Tile+k,j*Tile+l,i,j,k,l,road[0][0]);
					map[i*Tile+k][j*Tile+l]=tile[road[i][j]][k][l];
				}
			}
		}
	}
	for(i=0;i<MapY;i++){
		for(j=0;j<MapX;j++)
			printf("%d ",map[i][j]);
		printf("\n");
	}
}
int MakeMap::getMap(int y, int x){
	return map[y][x];
}