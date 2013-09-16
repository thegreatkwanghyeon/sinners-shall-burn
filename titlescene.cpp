#include "titlescene.h"

TitleScene::TitleScene(){
	font.loadFromFile("font/spike.ttf");
	text.setFont(font); 
	text.setString(L"num1 : ≈∏¿Ã∆≤ æ¿ \nnum2 : ≤≤¿”æ¿ \nnum3 : ºŒ¿Ã¥ıæ¿\nnum4 : ∆€¡Ò");
	text.setPosition(450.0f, 250.0f);

	std::vector<sf::Texture> textureList;
	sf::Texture circle;
	sf::Texture star;
	sf::Texture diamond;
	circle.loadFromFile("img/particles/circle.png");
	star.loadFromFile("img/particles/star.png");
	diamond.loadFromFile("img/particles/diamond.png");
	textureList.push_back(circle);
	textureList.push_back(star);
	textureList.push_back(diamond);

	particle = new ParticleEngine(textureList, sf::Vector2f(sf::Mouse::getPosition().x * 1.f, sf::Mouse::getPosition().y * 1.f) ,100);

}
TitleScene::~TitleScene(){
	
}
void TitleScene::update(sf::Event &event){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		particle->emit();
	particle->setLocation(sf::Vector2f(sf::Mouse::getPosition().x * 1.f, sf::Mouse::getPosition().y * 1.f));
	particle->update();
}

void TitleScene::draw(sf::RenderWindow &window){
	window.draw(text);
	particle->draw(window);
}