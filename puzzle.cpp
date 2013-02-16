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
			data[i][j]->init_animation();
		}
	}
	for(i=0;i<StackSize;i++){//스택은 그림 출력부와 num, init_ani 부분만 쓰게 된다.
		stack[i]=new PData(PStartX+430,((StackSize-1)-i)*50);
		stack[i]->num=-1;
		stack[i]->init_animation();
	}
	clickN=0;
	stackNum=0;

	flag=false;//업데이트 정지용.
}

void Puzzle::update(){
	int i,j,tp=0;
/*
	if(flag == true){//플래그는 어떤 블록이 3개 이상 맞아서 터졌을때 그에 맞는 애니메이션 진행동안은 다른 블록이 움직이거나 클릭을 받거나 하는걸 방지하기 위해 만듬.
		for(i=0;i<PuzzleSize;i++){
			for(j=0;j<PuzzleSize;j++){
				data[i][j]->update();//이거는 해줘야 애니메이션이 돌까 싶어서...
			}
		}
		for(i=0;i<StackSize;i++){
			stack[i]->draw(window);
		}
		return;
	}*/

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
						if(checkPuzzle() == 0){//일단 함수를 돌리고, 만약 0면 복구시킴. 1이면 플래그를 세운다. 
							tp = data[clickStack[0].y][clickStack[0].x]->num;
							data[clickStack[0].y][clickStack[0].x]->num = data[clickStack[1].y][clickStack[1].x]->num;
							data[clickStack[1].y][clickStack[1].x]->num = tp;//첫번째 그것과 두번쨰 그것을 '다시' 바꿈.
						}else{
							flag=true;
						}
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
	for(i=0;i<StackSize;i++)//스택 업데이트
		stack[i]->update();
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
			data[i][j]->draw(window);
		}
	}
	for(i=0;i<StackSize;i++){
		stack[i]->draw(window);
	}
}
/*
void Puzzle::addTile(std::string path, int _tileWidth, int _tileHeight){
	tileSizeX = _tileWidth;
	tileSizeY = _tileHeight;
	texture = tileset->tileSet(path, tileSizeX, tileSizeY);
}
*/
int Puzzle::checkPuzzle(){
	//원래 checkPuzzle은 퍼즐 내의 모든 3개짜리를 터트리는 용도였으나 콤보를 위해 1개 터지면 리턴하도록 설정된다.
	int i,j;//for문용
	int k;//예비

	srand(time(NULL));
	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			if(i >= 2 && data[i][j]->num == data[i-1][j]->num && data[i][j]->num == data[i-2][j]->num){//세로로 3개가 겹칠때.
				/*free(data[i-2][j]);
				free(data[i-1][j]);
				free(data[i][j]);*///굳이 free까지 안해도 되서 폐기된 계획안.
				printf("[%d %d %d | %d(j)] == break\n",i,i-1,i-2,j);
				stackInput(data[i][j]->num);//스택에 넣는다.
				k=i;
				while(1){
					if(k-3 < 0)
						break;
					data[k][j]->num=data[k-3][j]->num;//3칸 위의 것을 땡겨서 옴.
					data[k][j]->init_animation();
					k--;
				}//이러면 필연적으로 맨 위 3개가 비게된다.
				data[0][j]->num=rand()%PuzzleKind;
				data[0][j]->init_animation();
				while(1){
					data[1][j]->num=(rand())%PuzzleKind;
					if(data[1][j]->num != data[0][j]->num){
						data[1][j]->init_animation();
						break;
					}
				}
				while(1){
					data[2][j]->num=(rand())%PuzzleKind;
					if(data[2][j]->num != data[0][j]->num){
						data[2][j]->init_animation();
						break;
					}
				}

				printf("yea! block change!!!!!!!!(|)\n");
				return 1;
			}

			if(j >= 2 && data[i][j]->num == data[i][j-1]->num && data[i][j]->num == data[i][j-2]->num){//가로로 3개가 겹칠때.
				printf("[%d(i) | %d %d %d] == break\n",i,j,j-1,j-2);
				stackInput(data[i][j]->num);//스택에 넣는다.
				k=i;
				while(1){
					if(k-1 < 0)// k == 0와 같다.
						break;
					data[k][j]->num=data[k-1][j]->num;
					data[k][j]->init_animation();
					data[k][j-1]->num=data[k-1][j-1]->num;
					data[k][j-1]->init_animation();
					data[k][j-2]->num=data[k-1][j-2]->num;
					data[k][j-2]->init_animation();					
					k--;
				}//이러면 필연적으로 맨 위 1개가 비게된다.
				data[0][j]->num=rand()%PuzzleKind;
				data[0][j]->init_animation();
				while(1){
					data[0][j-1]->num=(rand())%PuzzleKind;
					if(data[0][j-1]->num != data[0][j]->num){
						data[0][j-1]->init_animation();
						break;
					}
				}
				while(1){
					data[0][j-2]->num=(rand())%PuzzleKind;
					if(data[0][j-2]->num != data[0][j]->num){
						data[0][j-2]->init_animation();
						break;
					}
				}

				printf("yea! block change!!!!!!!!(-)\n");
				return 1;
			}
		}
	}
	return 0;
	//0 : 겹치는게 없다. 이게 뜨면 걍 원상복구.
}

void Puzzle::stackInput(int num){
	int i;

	printf("Stack : %d %d %d %d %d. + %d.",stack[0]->num,stack[1]->num,stack[2]->num,stack[3]->num,stack[4]->num,num);
	if(stackNum == StackSize){//이미 스택이 찬 상태에서 넣을때.
		for(i=0;i<StackSize-1;i++){
			stack[i]->num=stack[i+1]->num;
		}
		stack[StackSize-1]->num=num;
	}else{//스택이 아직 다 안차있을때.
		stack[stackNum++]->num=num;
	}
	for(i=0;i<StackSize;i++)
		stack[i]->init_animation();
}/*
void Puzzle::drawStack(sf::RenderWindow &window){
	int i;
	for(i=StackSize-1;i>=0;i--){
		sprite.setPosition(PStartX+430,i*50);//퍼즐이 끝나는 부분부터 30 옆에 그려지게 됨.
		if(stackNum <= i)
			sprite.setTextureRect(tileset->getTileSet(36));
		else
			sprite.setTextureRect(tileset->getTileSet(stack[i]*4));
		window.draw(sprite);
	}
}*/