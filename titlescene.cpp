#include "titlescene.h"

TitleScene::TitleScene(){
	font.loadFromFile("font/spike.ttf");
	text.setFont(font); 
	text.setString(L"num1 : Ÿ��Ʋ �� \nnum2 : ���Ӿ� \nnum3 : ���̴���\nnum4 : ����");
	text.setPosition(450.0f, 250.0f);

	particle = new ParticleSystem(600, 600);
	particle->setAngleRange(0, 360);
	particle->setLifeRange(50, 100);
	particle->setStartColor(255, 0, 0, 0);
	particle->setEndColor(0, 255, 0, 255);
}
TitleScene::~TitleScene(){
	
}
void TitleScene::update(sf::Event &event){
	particle->update();
}

void TitleScene::draw(sf::RenderWindow &window){
	window.draw(text);
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		particle->setLocation(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
		particle->fuel(50);
	}
	particle->draw(window);
}