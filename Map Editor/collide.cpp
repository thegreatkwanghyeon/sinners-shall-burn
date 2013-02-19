#include "collide.h"

void Collide::initialize(){

	collide.loadFromFile("tiles/collide.png");
	no_collide.loadFromFile("tiles/no_collide.png");

	mapArea.left = 0;
	mapArea.width = MAPWIDTH;
	mapArea.top = 0;
	mapArea.height = MAPHEIGHT;

	for(unsigned int i = 0; i <= MAPHEIGHT/MAPTILEHEIGHT-1; i++){
		for(unsigned int j = 0; j <= MAPWIDTH/MAPTILEWIDTH-1; j++){
			tmpRect.left = j * MAPTILEWIDTH;
			tmpRect.top = i * MAPTILEHEIGHT;
			tmpRect.width = MAPTILEWIDTH;
			tmpRect.height = MAPTILEHEIGHT;
			rects.push_back(tmpRect);

			tmpChecker.sprite.setTexture(no_collide);
			tmpChecker.sprite.setPosition(j * MAPTILEWIDTH, i * MAPTILEHEIGHT);
			tmpChecker.num = 0;
			checkers.push_back(tmpChecker);
		}
	}
}

void Collide::check(int x, int y){
	if(mapArea.contains(x, y)){
		for(a=0;a<rects.size();a++){
			if(rects[a].contains(x, y))
				break;
		}

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			checkers[a].sprite.setTexture(collide);
			checkers[a].num = 1;
		}

		if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			checkers[a].sprite.setTexture(no_collide);
			checkers[a].num = 0;
		}		
	}
}

void Collide::draw(sf::RenderWindow &window){
	for(unsigned int k=0;k<checkers.size();k++){
		window.draw(checkers[k].sprite);
	}
}

void Collide::save(std::string string){
	saveFile = fopen(string.c_str(), "wb");
	for(unsigned int n=0;n<checkers.size();n++){
		fprintf(saveFile, "%d\n", checkers[n].num);
	}
}