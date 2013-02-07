#include "puzzle.h"
#include <stdlib.h>
#include <time.h>

//#include <time.hpp>
//Ver. 0.05 ==> 만들기 그리고 보여주기만 가능.
Puzzle::Puzzle(){
	int i,j;
	int rd;
	int chk[PuzzleSize*PuzzleSize+1]={0,};//체크용 배열.

	tileset = new TileSet();
	addTile("img/puzzle.JPG",50, 50);
	sprite.setTexture(texture);

	srand(time(NULL));
	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			while(1){
				rd=rand()%(PuzzleSize*PuzzleSize);//퍼즐의 사이즈의 제곱범위 내에서 난수 발생.

				if(i >= 2 && rd%PuzzleKind == data[i-2][j] && rd%PuzzleKind == data[i-1][j])//세로로 중복되는 경우.
					continue;
				if(j >= 2 && rd%PuzzleKind == data[i][j-2] && rd%PuzzleKind == data[i][j-1])//가로로 중복되는 경우.
					continue;

				if(chk[rd] == 0){
					chk[rd]=1;
					break;
				}
			}
			data[i][j]=rd%PuzzleKind;
		}
	}
}

void Puzzle::update(){
	int i,j;

	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && (mousePosition.y >= i*50 && mousePosition.y <= (i+1)*50) && (mousePosition.x >= j*50 && mousePosition.x <= (j+1)*50)){
			//마우스의 위치를 체크, 특정 버튼이 클릭되었을때의 처리를 한다...라고 추정되는 코드이다. 임시설치.
				printf("%d %d \n",i,j);

				if(data[j][i] < PuzzleKind){//임시코드.
					data[j][i]++;//임시코드.
					printf("clicked...!(%d %d)\n",i,j);
				}
				return;
			}
		}
	}

}

void Puzzle::draw(sf::RenderWindow &window){
	int i,j;
	mousePosition = sf::Mouse::getPosition(window);//마우스 위치를 mousePosition에 저장.
	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			sprite.setPosition(i*50, j*50);
			sprite.setTextureRect(tileset->getTileSet(data[i][j]));
			window.draw(sprite);
		}
	}
}

void Puzzle::addTile(std::string path, int _tileWidth, int _tileHeight){
	tileSizeX = _tileWidth;
	tileSizeY = _tileHeight;
	texture = tileset->tileSet(path, tileSizeX, tileSizeY);
}