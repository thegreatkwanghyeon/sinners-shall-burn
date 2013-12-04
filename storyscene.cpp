#include "storyscene.h"
#include "global.h"

StoryScene::StoryScene(){
	texture[0].loadFromFile("img/story/story1.png");
	texture[1].loadFromFile("img/story/story2.png");
	texture[2].loadFromFile("img/story/story3.png");
	texture[3].loadFromFile("img/story/story4.png");
	sprite.setTexture(texture[0]);
	sprite.setPosition(0,0);

	font.loadFromFile("font/aPinoL.ttf");
	text.setFont(font);
	text.setPosition(1240.0f, 665.0f);
	text.setCharacterSize(30);
	text.setString(sf::String(L"Press ENTER"));
	text.setOrigin(text.getLocalBounds().width,0);

	rec.setFillColor(sf::Color::Color(0,0,0,0));
	rec.setSize(sf::Vector2f(1280,720));
	rec.setPosition(0,0);

	delta.restart();
	alpha=0;
	storyNum=0;
	isPlus=true;
}
StoryScene::~StoryScene(){
}
void StoryScene::update(sf::Event &event){
	if(isPlus && alpha >= 255 && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
		isPlus=false;
	}
	if(delta.getElapsedTime().asSeconds() >= 0.015){
		delta.restart();
		if(isPlus){
			if(alpha < 255)
				alpha+=5;
				rec.setFillColor(sf::Color::Color(0,0,0,255-alpha));
		}else{
			alpha-=5;
			rec.setFillColor(sf::Color::Color(0,0,0,255-alpha));
			if(alpha == 0){
				isPlus=true;
				storyNum++;
				sprite.setTexture(texture[storyNum]);
			}
		}
	}
}

void StoryScene::draw(sf::RenderWindow &window){
	window.draw(sprite);
	window.draw(text);
	window.draw(rec);
}
int StoryScene::changeScene(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || storyNum >= Endstory)
		return 2;
	return -1;
}