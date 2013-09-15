#include "titlescene.h"

TitleScene::TitleScene(){
	font.loadFromFile("font/spike.ttf");
	text.setFont(font);
	text.setString(L"num1 : Å¸ÀÌÆ² ¾À \nnum2 : ²²ÀÓ¾À \nnum3 : ¼ÎÀÌ´õ¾À\nnum4 : ÆÛÁñ");
	text.setPosition(450.0f, 250.0f);
	particle = new ParticleEmitter(100);
	particle->setEmissionRate(0.1);
	particle->setAngleRange(30, 70);
	particle->setLifeRange(1, 2);
	particle->setSizeRange(10, 20);
	particle->setSpeedRange(100, 300);
	particle->setPositionRange(sf::Vector2i(500, 500),sf::Vector2i(500, 500));
	particle->setTexture("img/textures/particle.png");

}
TitleScene::~TitleScene(){
	
}
void TitleScene::update(sf::Event &event){
	particle->update(event);
}

void TitleScene::draw(sf::RenderWindow &window){
	window.draw(text);
	particle->draw(window);
}