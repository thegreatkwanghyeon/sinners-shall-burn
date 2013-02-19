#include "layer.h"

Layer::Layer(std::string string){
	saveName = string;
}

void Layer::initialize(int num, int width, int height, int currentLayer){
	selector.initialize(num, width, height, currentLayer);
	putter.initialize(num, currentLayer);
}

void Layer::setTexture(int num, int width, int height, int currentLayer){
	selector.setTexture(num, width, height, currentLayer);
	putter.setTexture(num, currentLayer);
}

void Layer::update(sf::RenderWindow &window, sf::Event &event){
	selector.select(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, event);
	putter.putTile(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, selector.getSelectedTile());	
	selector.draw(window);
}

void Layer::draw(sf::RenderWindow &window){
	putter.draw(window);
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