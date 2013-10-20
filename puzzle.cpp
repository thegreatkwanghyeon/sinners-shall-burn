#include "puzzle.h"

Puzzle::Puzzle(){
	int i,j;

	//타일셋. 힌트용
	tileset = new TileSet();
	texture.loadFromFile("img/hint.png");
	texture = tileset->tileSet("img/hint.png",55,55);
	sprite.setTexture(texture);
	sprite.setTextureRect(tileset->getTileSet(0));

	button = new Button("img/sbutton.png");
	button->setPosition(0,230);
	button->setText("HINT", 18);
	button->setClickSound("sounds/button/click.wav");
	button->setHoverSound("sounds/button/hover.wav");

	reButton = new Button("img/sbutton.png");
	reButton->setPosition(0,330);
	reButton->setText("REBUILD", 18);
	reButton->setClickSound("sounds/button/click.wav");
	reButton->setHoverSound("sounds/button/hover.wav");

	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			data[i][j] = new PData(PStartX+(j*PBlockSize),PStartY+(i*PBlockSize));
		}
	}
	//makePuzzle();
	
	for(i=0;i<StackSize;i++){
		stack[i]=new PData(PStartX+(PBlockSize+PBlockSize/2)+(i*PBlockSize),PStartY-(PBlockSize+(PBlockSize/5)));
		stack[i]->num=-1;
		stack[i]->init_animation();
	}
	clickN=0;
	stackNum=0;
	comboNum=0;
	hitNum=0;

	flag=false;
	move=false;

	tempNum=0;
	//limit1=0.0;
	hint=false;

	plusDamage=1.0;
	
	deltaTime=eTime.restart();

	//---버튼들 사용시 리젠시간 표시용 게이지들임.
	hGauge = new Gauge("img/timeGauge.PNG",100, 1, -1);
	hGauge->setPosition(sf::Vector2i(220,230));

	reGauge = new Gauge("img/timeGauge.PNG",100, 1, -1);
	reGauge->setPosition(sf::Vector2i(220,330));
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

void Puzzle::update(sf::Event &event){
	int i,j,tp;
	bool chkBlock=false;

	if(move == true){
		for(i=0;i<PuzzleSize;i++){
			for(j=0;j<PuzzleSize;j++){
				if(chkBreak[i][j] > 0){
					if(data[i][j]->y == PStartY+(i*PBlockSize)){
						chkBreak[i][j]=0;
					}else{
						data[i][j]->init_position(data[i][j]->x,data[i][j]->y+PBlockSize/5);
					}
					
					chkBlock=true;
				}
			}
		}
		if(chkBlock == false){
			move=false;
			checkPuzzle();
		}
		chkBlock=false;
	}
	if(flag == true){
		if(hint == true)
			hint=false;
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
			tempNum=0;

			movePuzzle();
			move=true;
		}else
			tempNum=tp;
		
		return;
	}

	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			if((mousePosition.y-15 > PStartY+(i*PBlockSize) && mousePosition.y-15 < PStartY+((i+1)*PBlockSize)) && 
				(mousePosition.x > PStartX+(j*PBlockSize) && mousePosition.x < PStartX+((j+1)*PBlockSize))){//마우스가 범위 내에 있을때.
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && data[i][j]->is_click == false){
					if(clickN == 2){//두곳을 거쳤을 때.

						tp = data[clickStack[0].y][clickStack[0].x]->num;
						data[clickStack[0].y][clickStack[0].x]->num = data[clickStack[1].y][clickStack[1].x]->num;
						data[clickStack[1].y][clickStack[1].x]->num = tp;

						if(checkPuzzle() == 0){//헛손질시
							tp = data[clickStack[0].y][clickStack[0].x]->num;
							data[clickStack[0].y][clickStack[0].x]->num = data[clickStack[1].y][clickStack[1].x]->num;
							data[clickStack[1].y][clickStack[1].x]->num = tp;
						}
						while(1){
							clickN--;
							data[clickStack[clickN].y][clickStack[clickN].x]->is_click=false;
							data[clickStack[clickN].y][clickStack[clickN].x]->init_animation();
							if(clickN <= 0)
								break;
						}
					}else{
						data[i][j]->is_click = true;
						data[i][j]->init_animation();

						clickStack[clickN].x=j;
						clickStack[clickN++].y=i;
					}
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
	checkPuzzleMore();

	button->update(event);
	if(button->checkMouseClick(event)){
		hint=true;
		button->disableButton();
		
		hTime.restart();
	}

	reButton->update(event);
	if(reButton->checkMouseClick(event)){
		makePuzzle();
		reButton->disableButton();

		reTime.restart();
	}

	//---
	if(!button->getButtonEneble() && hTime.getElapsedTime().asSeconds() >= 0.03){//3초 리미트
		//printf("%.3f\n",hTime.getElapsedTime().asSeconds());
		hGauge->setValue(-1);
		hTime.restart();
		if(hGauge->getValue() == 0){
			button->enableButton();
			hGauge->setValue(100);
		}
	}
	if(!reButton->getButtonEneble() && reTime.getElapsedTime().asSeconds() >= 0.15){//15초 리미트
		//printf("%.3f\n",hTime.getElapsedTime().asSeconds());
		reGauge->setValue(-1);
		reTime.restart();
		if(reGauge->getValue() == 0){
			reButton->enableButton();
			reGauge->setValue(100);
		}
	}

	hGauge->update();
	reGauge->update();
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

	if(hint == true)
		window.draw(sprite);
	button->draw(window);
	reButton->draw(window);

	if(!button->getButtonEneble())
		hGauge->draw(window);
	if(!reButton->getButtonEneble())
		reGauge->draw(window);
}
int Puzzle::checkPuzzle(){
	int i,j;
	char ComString[100];

	if(flag == true){//추가타 체크는 귀찮아서 걍 나눔...
		for(i=0;i<PuzzleSize;i++){
			for(j=0;j<PuzzleSize;j++){
				if(i >= 2 && data[i][j]->num == data[i-1][j]->num && data[i][j]->num == data[i-2][j]->num && (data[i][j]->is_break+data[i-1][j]->is_break+data[i-2][j]->is_break < 3)
					&& (data[i][j]->is_break == true || data[i-1][j]->is_break == true || data[i-2][j]->is_break == true)){//세로로 3개가 겹칠때.
					data[i][j]->is_break=true;
					data[i][j]->init_animation();
					data[i-1][j]->is_break=true;
					data[i-1][j]->init_animation();
					data[i-2][j]->is_break=true;
					data[i-2][j]->init_animation();
					//----플러스----//
					plusDamage *= 1.1;
				}
				if(j >= 2 && data[i][j]->num == data[i][j-1]->num && data[i][j]->num == data[i][j-2]->num && (data[i][j]->is_break+data[i][j-1]->is_break+data[i][j-2]->is_break < 3)
					&& (data[i][j]->is_break == true || data[i][j-1]->is_break == true || data[i][j-2]->is_break == true)){//가로로 3개가 겹칠때.
					data[i][j]->is_break=true;
					data[i][j]->init_animation();
					data[i][j-1]->is_break=true;
					data[i][j-1]->init_animation();
					data[i][j-2]->is_break=true;
					data[i][j-2]->init_animation();
					//----플러스----//
					plusDamage *= 1.1;
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
					//----플러스----//
					plusDamage *= 1.2;
				}else{
					stackInput(data[i][j]->num);
				}
				_snprintf(ComString, sizeof(ComString), "COMBO %d!!", comboNum);
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

				_snprintf(ComString, sizeof(ComString), "COMBO %d!!", comboNum);

				if(comboNum > 1){
					combo[comboNum-1]=data[i][j]->num;
					//----플러스----//
					plusDamage *= 1.2;
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

	for(i=0;i<PuzzleSize;i++){
		breakStack[i]=0;
		for(j=0;j<PuzzleSize;j++)
			chkBreak[i][j]=0;
	}
	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			if(data[i][j]->is_break == true){
				chkBreak[i][j]++;
				breakStack[j]++;
			}
		}
	}
	for(i=PuzzleSize-1;i>=1;i--){
		for(j=0;j<PuzzleSize;j++){
			if(chkBreak[i][j] > 0){
				chkBreak[i][j]=breakStack[j];
				chkBreak[i-1][j]=chkBreak[i][j];
			}
		}
	}

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
	//---
	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			if(chkBreak[i][j] > 0){
				data[i][j]->init_position(PStartX+(j*PBlockSize),PStartY+(i*PBlockSize)-(chkBreak[i][j]*PBlockSize));
			}
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
				if(i-2 >= 0 && data[i-2][j]->num == data[i][j]->num){
					sprite.setPosition(PStartX+(j*PBlockSize)-10,PStartY+((i-2)*PBlockSize)-10);
					return;
				}
				if(i-1 >= 0 && j+1 < PuzzleSize && data[i-1][j+1]->num == data[i][j]->num){
					sprite.setPosition(PStartX+((j+1)*PBlockSize)-10,PStartY+((i-1)*PBlockSize)-10);
					return;
				}
				if(i-1 >= 0 && j-1 >= 0 && data[i-1][j-1]->num == data[i][j]->num){
					sprite.setPosition(PStartX+((j-1)*PBlockSize)-10,PStartY+((i-1)*PBlockSize)-10);
					return;
				}

				if(i+3 < PuzzleSize && data[i+3][j]->num == data[i][j]->num){
					sprite.setPosition(PStartX+(j*PBlockSize)-10,PStartY+((i+3)*PBlockSize)-10);
					return;
				}
				if(i+2 < PuzzleSize && j+1 < PuzzleSize && data[i+2][j+1]->num == data[i][j]->num){
					sprite.setPosition(PStartX+((j+1)*PBlockSize)-10,PStartY+((i+2)*PBlockSize)-10);
					return;
				}
				if(i+2 < PuzzleSize && j-1 >= 0 && data[i+2][j-1]->num == data[i][j]->num){
					sprite.setPosition(PStartX+((j-1)*PBlockSize)-10,PStartY+((i+2)*PBlockSize)-10);
					return;
				}
			}
			if(j+1 < PuzzleSize && data[i][j]->num == data[i][j+1]->num){//케이스 2. 가로로 둘 겹칠때
				if(j-2 >= 0 && data[i][j-2]->num == data[i][j]->num){
					sprite.setPosition(PStartX+((j-2)*PBlockSize)-10,PStartY+(i*PBlockSize)-10);
					return;
				}
				if(j-1 >= 0 && i+1 < PuzzleSize && data[i+1][j-1]->num == data[i][j]->num){
					sprite.setPosition(PStartX+((j-1)*PBlockSize)-10,PStartY+((i+1)*PBlockSize)-10);
					return;
				}
				if(j-1 >= 0 && i-1 >= 0 && data[i-1][j-1]->num == data[i][j]->num){
					sprite.setPosition(PStartX+((j-1)*PBlockSize)-10,PStartY+((i-1)*PBlockSize)-10);
					return;
				}

				if(j+3 < PuzzleSize && data[i][j+3]->num == data[i][j]->num){
					sprite.setPosition(PStartX+((j+3)*PBlockSize)-10,PStartY+(i*PBlockSize)-10);
					return;
				}
				if(j+2 < PuzzleSize && i-1 >= 0 && data[i-1][j+2]->num == data[i][j]->num){
					sprite.setPosition(PStartX+((j+2)*PBlockSize)-10,PStartY+((i-1)*PBlockSize)-10);
					return;
				}
				if(j+2 < PuzzleSize && i+1 < PuzzleSize && data[i+1][j+2]->num == data[i][j]->num){
					sprite.setPosition(PStartX+((j+2)*PBlockSize)-10,PStartY+((i+1)*PBlockSize)-10);
					return;
				}
			}
			if(i+2 < PuzzleSize && data[i][j]->num == data[i+2][j]->num){//케이스 3. 하나 띄고 세로
				if(j-1 >= 0 && data[i+1][j-1]->num == data[i][j]->num){
					sprite.setPosition(PStartX+((j-1)*PBlockSize)-10,PStartY+((i+1)*PBlockSize)-10);
					return;
				}
				if(j+1 < PuzzleSize && data[i+1][j+1]->num == data[i][j]->num){
					sprite.setPosition(PStartX+((j+1)*PBlockSize)-10,PStartY+((i+1)*PBlockSize)-10);
					return;
				}
			}
			if(j+2 < PuzzleSize && data[i][j]->num == data[i][j+2]->num){//케이스 4. 하나 띄고 가로
				if(i-1 >= 0 && data[i-1][j+1]->num == data[i][j]->num){
					sprite.setPosition(PStartX+((j+1)*PBlockSize)-10,PStartY+((i-1)*PBlockSize)-10);
					return;
				}
				if(i+1 < PuzzleSize && data[i+1][j+1]->num == data[i][j]->num){
					sprite.setPosition(PStartX+((j+1)*PBlockSize)-10,PStartY+((i+1)*PBlockSize)-10);
					return;
				}
			}
		}
	}
	deltaTime=eTime.restart();
	makePuzzle();//리빌드
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

	hitNum++;
}

void Puzzle::makePuzzle(){
	int i,j;
	int rd;
	srand(time(NULL));
	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			data[i][j]->num=-1;
		}
	}
	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			while(1){
				rd=rand()%PuzzleKind;

				if(i >= 2 && PuzzleElement[rd%PuzzleKind] == data[i-2][j]->num && PuzzleElement[rd%PuzzleKind] == data[i-1][j]->num)//세로로 중복되는 경우.
					continue;
				if(j >= 2 && PuzzleElement[rd%PuzzleKind] == data[i][j-2]->num && PuzzleElement[rd%PuzzleKind] == data[i][j-1]->num)//가로로 중복되는 경우.
					continue;

				break;
			}
			data[i][j]->num=PuzzleElement[rd%PuzzleKind];
			data[i][j]->init_animation();
		}
	}
}
void Puzzle::setElement(int Element[]){
	int i;
	for(i=0;i<PuzzleKind;i++){
		PuzzleElement[i] = Element[i];
		//printf("%d \n",PuzzleElement[i]);
	}
	makePuzzle();
}
float Puzzle::getPlusDamage(){
	return plusDamage;
}
void Puzzle::setPlusDamage(float _damage){
	plusDamage = _damage;
}