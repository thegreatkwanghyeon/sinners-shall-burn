#include "puzzle.h"
#include <stdlib.h>
//#include <time.hpp>
//Ver. 0.05 ==> 만들기 그리고 보여주기만 가능.
Puzzle::Puzzle(){
	int i,j;
	sf::Clock time_user;
	tileset = new TileSet();
	addTile("img/puzzle.JPG",50, 50);
	sprite.setTexture(texture);

	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			data[i][j] = make_RandomNum(time_user,i,j);//처음 값은 0과 안겹치게, 즉 막나오고 두번째부턴 앞값과 비교되도록 함.
		}
	}
}

void Puzzle::update(){

	//일단 비워놓음.

}

void Puzzle::draw(sf::RenderWindow &window){
	int i,j;
	for(i=0;i<PuzzleSize;i++){
		for(j=0;j<PuzzleSize;j++){
			sprite.setPosition(i*50, j*50);
			sprite.setTextureRect(tileset->getTileSet(data[i][j]));
			window.draw(sprite);
		}
	}
}

int Puzzle::make_RandomNum(sf::Clock time_user, int i, int j){
	sf::Time t2=time_user.getElapsedTime();//시간을 받음. 이렇게 안하면 같은값만 t2가 준다.
	int rd;//비교해서 거르려면 rd에 저장 필요함.

	srand(t2.asMilliseconds());
	while(1){
		rd=rand()%PuzzleKind;
		if((rd != data[i-1][j] || i == 0) && (rd != data[i][j-1] || j == 0))//위 값과 앞의 값을 가지고 비교. 같은게 나오지 않도록 함.
			break;
	}
	printf("<%d>\n",rd);
	//sf::sleep(sf::Time duration);
	return rd;
}

void Puzzle::addTile(std::string path, int _tileWidth, int _tileHeight){
	tileSizeX = _tileWidth;
	tileSizeY = _tileHeight;
	texture = tileset->tileSet(path, tileSizeX, tileSizeY);
}