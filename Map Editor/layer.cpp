#include "layer.h"

Layer::Layer(std::string string){
	saveName = string;
}

void Layer::setTexture(int num){
	selector.initialize(num);
	putter.initialize(num);
}

void Layer::update(sf::RenderWindow &window){
	selector.select(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	putter.putTile(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, selector.getSelectedTile());	
}

void Layer::draw(sf::RenderWindow &window){
	putter.draw(window);
	selector.draw(window);
}

void Layer::save(){
	saveMap = fopen(saveName.c_str(), "wb");
	for(unsigned int i=0;i<putter.getMap().size();i++){
		fprintf(saveMap, "%f\t%f\t%d\t%d\t%d\t%d\t%s\n", putter.getMap()[i].sprite.getPosition().x, putter.getMap()[i].sprite.getPosition().y, putter.getMap()[i].sprite.getTextureRect().left, putter.getMap()[i].sprite.getTextureRect().width, putter.getMap()[i].sprite.getTextureRect().top, putter.getMap()[i].sprite.getTextureRect().height, putter.getMap()[i].string.c_str());
		//fwrite(&putter.getMap()[i].sprite.getPosition().x, sizeof(float), 1, saveMap);
		//fwrite(&putter.getMap()[i].sprite.getPosition().y, sizeof(float), 1, saveMap);
		//fwrite(&putter.getMap()[i].sprite.getTextureRect().left, sizeof(int), 1, saveMap);
		//fwrite(&putter.getMap()[i].sprite.getTextureRect().width, sizeof(int), 1, saveMap);
		//fwrite(&putter.getMap()[i].sprite.getTextureRect().top, sizeof(int), 1, saveMap);
		//fwrite(&putter.getMap()[i].sprite.getTextureRect().height, sizeof(int), 1, saveMap);
		//fwrite(&putter.getMap()[i].string, putter.getMap()[i].string.size(), 1, saveMap);
	}
	fclose(saveMap);
}