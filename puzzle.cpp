#include "puzzle.h"

Puzzle::Puzzle(){
	int i,j;

	font.loadFromFile("font/spike.ttf");
	text.setFont(font);
	text.setString(L"모든 블록이 터졌습니다...교대합니다");
	text.setPosition(0.0f, 0.0f);

	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			data[i][j] = new PData(PStartX+(j*PBlockSize),PStartY+(i*PBlockSize));
		}
	}
	makePuzzle();
	
	for(i=0;i<StackSize;i++){
		stack[i]=new PData(PStartX+(PBlockSize*PuzzleSize)+20,((StackSize-1)-i)*50+PStartY);
		stack[i]->num=-1;
		stack[i]->init_animation();
	}
	clickN=0;
	stackNum=0;
	comboNum=0;

	flag=false;
	change=false;

	tempNum=0;
	limit=0;
	
	deltaTime=eTime.restart();
}

Puzzle::~Puzzle(){
	int i,j;

	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){ 
			delete data[i][j];
		}
	}
	for(i=0;i<StackSize;i++)
		delete stack[i];
}

void Puzzle::update(){
	int i,j,tp=0;

	if(change == true){
		//printf("%d %d!\n",deltaTime.asMilliseconds(),time_limit);
		limit-=1;
		//printf("[[[%d]]]\n",limit);
		if(limit <= 0){
			limit=0;
			change = false;
			makePuzzle();
		}
		deltaTime=eTime.restart();
		return;
	}
	if(flag == true){
		for(i=0;i<PuzzleSize;i++){
			for(j=0;j<PuzzleSize;j++){
				data[i][j]->update();
			}
		}
		for(i=0;i<StackSize;i++){
			stack[i]->update();
		}
		
		tp = data[temp.y][temp.x]->getLocation();
		//printf("%d %d\n",tp,tempNum);
		
		if(tp < tempNum){
			flag=false;
			tempNum=0;

			movePuzzle();
			/*
			if(direction == 1){
				data[temp.y-2][temp.x]->is_break=false;
				data[temp.y-2][temp.x]->init_animation();
				data[temp.y-1][temp.x]->is_break=false;
				data[temp.y-1][temp.x]->init_animation();
			}else{
				data[temp.y][temp.x-1]->is_break=false;
				data[temp.y][temp.x-1]->init_animation();
				data[temp.y][temp.x-2]->is_break=false;
				data[temp.y][temp.x-2]->init_animation();
			}
			data[temp.y][temp.x]->is_break=false;
			data[temp.y][temp.x]->init_animation();*/
			//---

			checkPuzzle();
		}else
			tempNum=tp;
		
		return;
	}

	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){

			if((mousePosition.y >= PStartY+(i*PBlockSize) && mousePosition.y <= PStartY+((i+1)*PBlockSize)) && 
				(mousePosition.x >= PStartX+(j*PBlockSize) && mousePosition.x <= PStartX+((j+1)*PBlockSize))){//마우스가 범위 내에 있을때.
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && data[i][j]->is_click == false){
					data[i][j]->is_click = true;
					data[i][j]->init_animation();

					clickStack[clickN].x=j;
					clickStack[clickN++].y=i;
				}else if(!(sf::Mouse::isButtonPressed(sf::Mouse::Left)) && clickN != 0){//키를 손에서 떼었을때.
					if(clickN == 2){//두곳을 거쳤을 때.

						tp = data[clickStack[0].y][clickStack[0].x]->num;
						data[clickStack[0].y][clickStack[0].x]->num = data[clickStack[1].y][clickStack[1].x]->num;
						data[clickStack[1].y][clickStack[1].x]->num = tp;

						if(checkPuzzle() == 0){//헛손질시
							tp = data[clickStack[0].y][clickStack[0].x]->num;
							data[clickStack[0].y][clickStack[0].x]->num = data[clickStack[1].y][clickStack[1].x]->num;
							data[clickStack[1].y][clickStack[1].x]->num = tp;
						}
					}
					while(1){
						clickN--;
						data[clickStack[clickN].y][clickStack[clickN].x]->is_click=false;
						data[clickStack[clickN].y][clickStack[clickN].x]->init_animation();
						if(clickN <= 0)
							break;
					}
				}
			}
			data[i][j]->update();
		}
	}
	for(i=0;i<StackSize;i++)
		stack[i]->update();
}

void Puzzle::draw(sf::RenderWindow &window){
	int i,j;
	mousePosition = sf::Mouse::getPosition(window);
	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			data[i][j]->draw(window);
		}
	}
	for(i=0;i<StackSize;i++){
		stack[i]->draw(window);
	}
	if(change == true){
		window.draw(text);
	}
}
int Puzzle::checkPuzzle(){
	int i,j;

	if(flag == true){//추가타 체크는 귀찮아서 걍 나눔...
		for(i=0;i<PuzzleSize;i++){
			for(j=0;j<PuzzleSize;j++){
				if(i >= 2 && data[i][j]->num == data[i-1][j]->num && data[i][j]->num == data[i-2][j]->num
					&& (data[i][j]->is_break == true || data[i-1][j]->is_break == true || data[i-2][j]->is_break == true)){//세로로 3개가 겹칠때.
					data[i][j]->is_break=true;
					data[i][j]->init_animation();
					data[i-1][j]->is_break=true;
					data[i-1][j]->init_animation();
					data[i-2][j]->is_break=true;
					data[i-2][j]->init_animation();
				}
				if(j >= 2 && data[i][j]->num == data[i][j-1]->num && data[i][j]->num == data[i][j-2]->num
					&& (data[i][j]->is_break == true || data[i][j-1]->is_break == true || data[i][j-2]->is_break == true)){//가로로 3개가 겹칠때.
					data[i][j]->is_break=true;
					data[i][j]->init_animation();
					data[i][j-1]->is_break=true;
					data[i][j-1]->init_animation();
					data[i][j-2]->is_break=true;
					data[i][j-2]->init_animation();
				}
			}
		}
		return 0;
	}

	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			if(i >= 2 && data[i][j]->num == data[i-1][j]->num && data[i][j]->num == data[i-2][j]->num){//세로로 3개가 겹칠때.
				comboNum++;

				if(comboNum > 1){
					combo[comboNum-1]=data[i][j]->num;
				}else{
					stackInput(data[i][j]->num);
				}
				//---

				flag=true;

				data[i-2][j]->is_break=true;
				data[i-2][j]->init_animation();
				data[i-1][j]->is_break=true;
				data[i-1][j]->init_animation();
				data[i][j]->is_break=true;
				data[i][j]->init_animation();

				checkPuzzle();

				temp.x=j;
				temp.y=i;

				return 1;
			}
			if(j >= 2 && data[i][j]->num == data[i][j-1]->num && data[i][j]->num == data[i][j-2]->num){//가로로 3개가 겹칠때.
				comboNum++;

				if(comboNum > 1){
					combo[comboNum-1]=data[i][j]->num;
				}else{
					stackInput(data[i][j]->num);
				}
				

				flag=true;

				data[i][j-2]->is_break=true;
				data[i][j-2]->init_animation();
				data[i][j-1]->is_break=true;
				data[i][j-1]->init_animation();
				data[i][j]->is_break=true;
				data[i][j]->init_animation();

				checkPuzzle();

				temp.x=j;
				temp.y=i;

				return 1;
			}
		}
	}
	//---
	comboNum=0;
	return 0;
}

void Puzzle::movePuzzle(){
	int i,j,k;
	int rd,tp,cnt=0;

	deltaTime=eTime.restart();
	srand(deltaTime.asMilliseconds());


	for(i=PuzzleSize-2;i>=0;i--){//밑에서 두번쨰부터 시작. 아래가 비었으면 내린다.
		for(j=0;j<PuzzleSize;j++){
			if(data[i+1][j]->is_break == true && data[i][j]->is_break == false){
				cnt++;
				for(k=i+1;k<PuzzleSize;k++){
					if(k+1 == PuzzleSize || data[k+1][j]->is_break == false)
						break;
				}
				data[k][j]->num=data[i][j]->num;
				data[k][j]->is_break=false;
				data[i][j]->is_break=true;
			}
		}
	}
	//---
	tp=-1;
	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			if(data[i][j]->is_break == true){
				data[i][j]->is_break=false;
				while(1){
					rd=rand()%PuzzleKind;
					if(rd != tp){
						data[i][j]->num=rd;
						tp=rd;
						break;
					}
				}
			}
			data[i][j]->init_animation();
		}
	}
}
void Puzzle::checkPuzzleMore(){
	int i,j;

	//startTime=0.0;
	//limit=100;

	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			if(i+1 < PuzzleSize && data[i][j]->num == data[i+1][j]->num){//케이스 1. 세로로 둘 겹칠 때
				if(i-2 >= 0 && data[i-2][j]->num == data[i][j]->num)
					return;
				if(i-1 >= 0 && j+1 < PuzzleSize && data[i-1][j+1]->num == data[i][j]->num)
					return;
				if(i-1 >= 0 && j-1 >= 0 && data[i-1][j-1]->num == data[i][j]->num)
					return;

				if(i+3 < PuzzleSize && data[i+3][j]->num == data[i][j]->num)
					return;
				if(i+2 < PuzzleSize && j+1 < PuzzleSize && data[i+2][j+1]->num == data[i][j]->num)
					return;
				if(i+2 < PuzzleSize && j-1 >= 0 && data[i+2][j-1]->num == data[i][j]->num)
					return;
			}
			if(j+1 < PuzzleSize && data[i][j]->num == data[i][j+1]->num){//케이스 2. 가로로 둘 겹칠때
				if(j-2 >= 0 && data[i][j-2]->num == data[i][j]->num)
					return;
				if(j-1 >= 0 && i+1 < PuzzleSize && data[i+1][j-1]->num == data[i][j]->num)
					return;
				if(j-1 >= 0 && i-1 >= 0 && data[i-1][j-1]->num == data[i][j]->num)
					return;

				if(j+3 < PuzzleSize && data[i][j+3]->num == data[i][j]->num)
					return;
				if(j+2 >= 0 && i-1 >= 0 && data[i-1][j+2]->num == data[i][j]->num)
					return;
				if(j+2 >= 0 && i+1 < PuzzleSize && data[i+1][j+2]->num == data[i][j]->num)
					return;
			}
			if(i+2 < PuzzleSize && data[i][j]->num == data[i+2][j]->num){//케이스 3. 하나 띄고 세로
				if(j-1 >= 0 && data[i+1][j-1]->num == data[i][j]->num)
					return;
				if(j+1 < PuzzleSize && data[i+1][j+1]->num == data[i][j]->num)
					return;
			}
			if(j+2 < PuzzleSize && data[i][j]->num == data[i][j+2]->num){//케이스 4. 하나 띄고 가로
				if(i-1 >= 0 && data[i-1][j+1]->num == data[i][j]->num)
					return;
				if(i+1 < PuzzleSize && data[i+1][j+1]->num == data[i][j]->num)
					return;
			}
		}
	}
	//deltaTime=eTime.restart();
	limit=100;
	change=true;
}

void Puzzle::stackInput(int num){
	int i;

	if(stackNum == StackSize){
		for(i=0;i<StackSize-1;i++){
			stack[i]->num=stack[i+1]->num;
		}
		stack[StackSize-1]->num=num;
	}else{
		stack[stackNum++]->num=num;
	}
	for(i=0;i<StackSize;i++)
		stack[i]->init_animation();
}

void Puzzle::makePuzzle(){
	int i,j;
	int rd;
	deltaTime = eTime.restart();
	srand(deltaTime.asMicroseconds());
	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			while(1){
				rd=rand()%PuzzleKind;

				if(i >= 2 && rd%PuzzleKind == data[i-2][j]->num && rd%PuzzleKind == data[i-1][j]->num)//세로로 중복되는 경우.
					continue;
				if(j >= 2 && rd%PuzzleKind == data[i][j-2]->num && rd%PuzzleKind == data[i][j-1]->num)//가로로 중복되는 경우.
					continue;

				break;
			}
			data[i][j]->num=rd%PuzzleKind;
			data[i][j]->init_animation();
		}
	}
}