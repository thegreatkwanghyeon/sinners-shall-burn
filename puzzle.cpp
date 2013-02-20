#include "puzzle.h"

Puzzle::Puzzle(){
	int i,j;

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
	direction=0;
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
		
		if(tp < tempNum){
			flag=false;

			movePuzzle(temp,direction);
			
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
			data[temp.y][temp.x]->init_animation();
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
}
int Puzzle::checkPuzzle(){//direction | 1 : 가로 | 2 : 세로 |
	int i,j;

	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			if(i >= 2 && data[i][j]->num == data[i-1][j]->num && data[i][j]->num == data[i-2][j]->num){//세로로 3개가 겹칠때.
				comboNum++;
				direction=1;

				if(comboNum > 1){
					combo[comboNum-1]=data[i][j]->num;
				}else{
					stackInput(data[i][j]->num);
				}

				flag=true;
				temp.x=j;
				temp.y=i;
				tempNum=-1;

				data[i-2][j]->is_break=true;
				data[i-2][j]->init_animation();
				data[i-1][j]->is_break=true;
				data[i-1][j]->init_animation();
				data[i][j]->is_break=true;
				data[i][j]->init_animation();

				return 1;
			}
			if(j >= 2 && data[i][j]->num == data[i][j-1]->num && data[i][j]->num == data[i][j-2]->num){//가로로 3개가 겹칠때.
				comboNum++;
				direction=0;

				if(comboNum > 1){
					combo[comboNum-1]=data[i][j]->num;
				}else{
					stackInput(data[i][j]->num);
				}

				flag=true;
				temp.x=j;
				temp.y=i;
				tempNum=-1;

				data[i][j-2]->is_break=true;
				data[i][j-2]->init_animation();
				data[i][j-1]->is_break=true;
				data[i][j-1]->init_animation();
				data[i][j]->is_break=true;
				data[i][j]->init_animation();

				return 1;
			}
		}
	}
	//---
	comboNum=0;
	return 0;
}

void Puzzle::movePuzzle(sf::Vector2i tp, int d){
	int i,j;
	int rd;

	deltaTime=eTime.restart();
	srand(deltaTime.asMilliseconds());
	i=tp.y;
	j=tp.x;
	//---
	if(d == 0){//가로
		while(1){
			if(i <= 0)
				break;

			data[i][j]->num=data[i-1][j]->num;
			data[i][j]->init_animation();
			data[i][j-1]->num=data[i-1][j-1]->num;
			data[i][j-1]->init_animation();
			data[i][j-2]->num=data[i-1][j-2]->num;
			data[i][j-2]->init_animation();

			i--;			
		}
		rd=rand()%PuzzleKind;
		data[0][j]->num=rd;
		data[0][j]->init_animation();
		while(1){//중복방지
			rd=rand()%PuzzleKind;
			data[0][j-1]->num=rd;
			if(data[0][j]->num != data[0][j-1]->num){
				data[0][j-1]->init_animation();
				break;
			}
		}
		while(1){//중복방지
			rd=rand()%PuzzleKind;
			data[0][j-2]->num=rd;
			if(data[0][j]->num != data[0][j-2]->num){
				data[0][j-2]->init_animation();
				break;
			}
		}
	}else{//세로
		while(1){
			if(i <= 2)
				break;

			data[i][j]->num=data[i-3][j]->num;
			data[i][j]->init_animation();

			i--;
		}
		rd=rand()%PuzzleKind;
		data[0][j]->num=rd;
		data[0][j]->init_animation();
		while(1){//중복방지
			rd=rand()%PuzzleKind;
			data[1][j]->num=rd;
			if(data[0][j]->num != data[1][j]->num){
				data[1][j]->init_animation();
				break;
			}
		}
		while(1){//중복방지
			rd=rand()%PuzzleKind;
			data[2][j]->num=rd;
			if(data[0][j]->num != data[2][j]->num){
				data[2][j]->init_animation();
				break;
			}
		}
	}
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