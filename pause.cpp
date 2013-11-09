#include "pause.h"

Pause::Pause(){
	isPause=false;
	endFlag=false;
	titleFlag=false;

	cButton = new Button("img/startbutton.png");
	cButton->setClickSound("sounds/button/click.wav");
	cButton->setHoverSound("sounds/button/hover.wav");
	cButton->setPosition(510,200);
	cButton->setText("continue");

	tButton = new Button("img/startbutton.png");
	tButton->setClickSound("sounds/button/click.wav");
	tButton->setHoverSound("sounds/button/hover.wav");
	tButton->setPosition(510,400);
	tButton->setText("back to title");

	endButton = new Button("img/startbutton.png");
	endButton->setClickSound("sounds/button/click.wav");
	endButton->setHoverSound("sounds/button/hover.wav");
	endButton->setPosition(510,500);
	endButton->setText("end game");

	slider = new Slider(&soundVolume, "img/slider/slider.png", "img/slider/handle.png");
	slider->setPosition(390,300);
	slider->setLimit(100);
}
Pause::~Pause(){
	delete cButton;
	delete endButton;
	delete tButton;
}
void Pause::update(sf::Event &event){
	cButton->update(event);
	tButton->update(event);
	endButton->update(event);
	slider->update();
	if(cButton->checkMouseClick(event))
		pauseOff();//콘티뉴버튼 누르면 계속 진행...
	if(endButton->checkMouseClick(event))
		endFlag=true;
	if(tButton->checkMouseClick(event))
		titleFlag=true;
}
void Pause::draw(sf::RenderWindow &window){
	sf::RectangleShape rec;//화면 검게 덮어줄 사각형
	rec.setPosition(0,0);
	rec.setSize(sf::Vector2f(1280,700));
	rec.setFillColor(sf::Color::Color(0,0,0,200));//반투명 검정?
	window.draw(rec);
	//---
	cButton->draw(window);
	tButton->draw(window);
	endButton->draw(window);
	slider->draw(window);
}
bool Pause::getState(){
	return isPause; 
}
void Pause::pauseOn(){
	isPause=true;
}
void Pause::pauseOff(){
	isPause=false;
}
bool Pause::isEnd(){
	return endFlag;
}
bool Pause::isGoTitle(){
	return titleFlag;
}