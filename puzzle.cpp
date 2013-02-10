#include "puzzle.h"
//#include <time.h>
//Ver. 0.05 ==> 만들기 그리고 보여주기만 가능.
Puzzle::Puzzle(){
	int i,j;
	int rd; //랜덤값을 받아두는 변수.
	int chk[PuzzleSize*PuzzleSize+1]={0,};//체크용 배열.

	//tileset = new TileSet();
	//addTile("img/puzzle.JPG",50, 50);
	//sprite.setTexture(texture);

	srand(time(NULL));
	for(i=0;i<PuzzleSize;i++){//기본 퍼즐 생성.
		for(j=0;j<PuzzleSize;j++){
			data[i][j] = new PData(PStartX+(j*PBlockSize),PStartY+(i*PBlockSize));//생성.
			printf("%d %d ok.\n",i,j);
			//---

			while(1){
				rd=rand()%(PuzzleSize*PuzzleSize);//퍼즐의 사이즈의 제곱범위 내에서 난수 발생.

				if(i >= 2 && rd%PuzzleKind == data[i-2][j]->num && rd%PuzzleKind == data[i-1][j]->num)//세로로 중복되는 경우.
					continue;
				if(j >= 2 && rd%PuzzleKind == data[i][j-2]->num && rd%PuzzleKind == data[i][j-1]->num)//가로로 중복되는 경우.
					continue;

				if(chk[rd] == 0){
					chk[rd]=1;
					break;
				}
			}
			data[i][j]->num=rd%PuzzleKind;
			data[i][j]->is_click=false;//클릭 확인 변수는 거짓으로 설정.
			data[i][j]->init_animation();
		}
	}
	clickN=0;
}

void Puzzle::update(){
	int i,j,tp=0;

	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			/*클릭 인식의 기본 원리 설명
			1. 클릭한 위치(cx,cy)를 -1로 해두고, 만약 클릭시 그 값으로 바꿈.
			2. 이후 마우스 버튼이 눌린 체로 cx나 cy가 i,j와 다르면(즉 옆으로 드래그하면) 둘의 값을 바꿀 준비를 한다.
			3. 만약 클릭한채로 제 3의 위치로 가면 취소한다.
			4. 마우스를 떼었을때 2곳에 머물렀다면 둘을 바꾸고, 아니면 취소한다.
			*/
			/*
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && (mousePosition.y >= PStartY+(i*PBlockSize) && 
				mousePosition.y <= PStartY+((i+1)*PBlockSize) && (mousePosition.x >= PStartX+(j*PBlockSize) && mousePosition.x <= PStartX+((j+1)*PBlockSize)){
			//마우스의 위치를 체크, 특정 버튼이 클릭되었을때의 처리를 한다.
				if((cx != j || cy != i) && cnum != 0){//다른곳을 누른 후 드래그
					cnum++;
				}else if(cnum == 0){
					cnum++;
					cx=j;
					cy=i;
				}
				printf("%d %d \n",i,j);
				
			}
			if(!(sf::Mouse::isButtonPressed(sf::Mouse::Left))){//버튼에서 손을 떼었을때.
				if(cnum == 1 && data[cx][cy] < PuzzleKind){//한곳만 클릭, 이후 마우스를 놓았다면?임. 차후 패치.
					data[cx][cy]++;
					printf("good!(%d %d)\n",cx,cy);
				}
				cnum=0;
			}*/
			if((mousePosition.y >= PStartY+(i*PBlockSize) && mousePosition.y <= PStartY+((i+1)*PBlockSize)) && 
				(mousePosition.x >= PStartX+(j*PBlockSize) && mousePosition.x <= PStartX+((j+1)*PBlockSize))){//마우스가 범위 내에 있을때.
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && data[i][j]->is_click == false){//클릭하지 않은곳을 클릭했다. 클릭한 곳을 또 클릭하는건 의미가 없겠지.
					data[i][j]->is_click = true;
					printf("%d %d boom!!!\n",i,j);
					data[i][j]->init_animation();

					clickStack[clickN].x=j;
					clickStack[clickN++].y=i;//클릭스택에 담음.
				}else if(!(sf::Mouse::isButtonPressed(sf::Mouse::Left)) && clickN != 0){//키를 손에서 떼었을때.
					if(clickN == 2){//두곳을 거쳤을 때.
						printf("swap!!!!!(%d %d)\n",data[clickStack[0].y][clickStack[0].x]->num,data[clickStack[1].y][clickStack[1].x]->num);
						tp = data[clickStack[0].y][clickStack[0].x]->num;
						data[clickStack[0].y][clickStack[0].x]->num = data[clickStack[1].y][clickStack[1].x]->num;
						data[clickStack[1].y][clickStack[1].x]->num = tp;//첫번째 그것과 두번쨰 그것을 바꿈.
						printf("swap is end(%d %d)\n",data[clickStack[0].y][clickStack[0].x]->num,data[clickStack[1].y][clickStack[1].x]->num);
					}
					while(1){
						clickN--;
						data[clickStack[clickN].y][clickStack[clickN].x]->is_click=false;
						data[clickStack[clickN].y][clickStack[clickN].x]->init_animation();
						if(clickN <= 0)
							break;
					}
					//data[i][j]->is_click = false;
				}
			}
			data[i][j]->update();
		}
	}

}

void Puzzle::draw(sf::RenderWindow &window){
	int i,j;
	mousePosition = sf::Mouse::getPosition(window);//마우스 위치를 mousePosition에 저장.
	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			//draw함수에는 draw 만 쓰는게 좋지
			//sprite.setPosition(i*PBlockSize, j*PBlockSize);//PBlockSize==50
			//sprite.setTextureRect(tileset->getTileSet(data[i][j]));
			//window.draw(sprite);
			data[i][j]->draw(window,i*PBlockSize, j*PBlockSize);
		}
	}
}
/*
void Puzzle::addTile(std::string path, int _tileWidth, int _tileHeight){
	tileSizeX = _tileWidth;
	tileSizeY = _tileHeight;
	texture = tileset->tileSet(path, tileSizeX, tileSizeY);
}
*/