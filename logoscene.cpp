#include "logoscene.h"
#include "global.h"

LogoScene::LogoScene(){
	texture[0].loadFromFile("img/logo1.png");
	texture[1].loadFromFile("img/logo2.png");
	sprite.setTexture(texture[0]);
	sprite.setPosition(0,0);

	rec.setFillColor(sf::Color::Color(0,0,0,0));
	rec.setSize(sf::Vector2f(1280,720));
	rec.setPosition(0,0);

	delta.restart();
	alpha=0;
	logoNum=0;
}
LogoScene::~LogoScene(){
}
void LogoScene::update(sf::Event &event){
	if(alpha >= 500){
		logoNum++;
		sprite.setTexture(texture[logoNum]);
		alpha=0;
	}
	if(delta.getElapsedTime().asSeconds() >= 0.03){
		delta.restart();
		alpha+=5;
		if(alpha <= 250)
			rec.setFillColor(sf::Color::Color(0,0,0,250-alpha));
		else
			rec.setFillColor(sf::Color::Color(0,0,0,alpha-250));
	}
}

void LogoScene::draw(sf::RenderWindow &window){
	window.draw(sprite);
	window.draw(rec);
}
int LogoScene::changeScene(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || logoNum >= EndLogo)
		return 1;
	return -1;
}