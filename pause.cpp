#include "pause.h"

Pause::Pause(){
	isPause=false;
	endFlag=false;
	titleFlag=false;

	cButton = new Button("img/startbutton.png");
	cButton->setClickSound("sounds/button/click.wav");
	cButton->setHoverSound("sounds/button/hover.wav");
	cButton->setPosition(500,300);
	cButton->setText("continue");

	tButton = new Button("img/startbutton.png");
	tButton->setClickSound("sounds/button/click.wav");
	tButton->setHoverSound("sounds/button/hover.wav");
	tButton->setPosition(500,400);
	tButton->setText("back to title");

	endButton = new Button("img/startbutton.png");
	endButton->setClickSound("sounds/button/click.wav");
	endButton->setHoverSound("sounds/button/hover.wav");
	endButton->setPosition(500,500);
	endButton->setText("end game");
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
	if(cButton->checkMouseClick(event))
		pauseOff();//��Ƽ����ư ������ ��� ����...
	if(endButton->checkMouseClick(event))
		endFlag=true;
	if(tButton->checkMouseClick(event))
		titleFlag=true;
}
void Pause::draw(sf::RenderWindow &window){
	sf::RectangleShape rec;//ȭ�� �˰� ������ �簢��
	rec.setPosition(0,0);
	rec.setSize(sf::Vector2f(1280,700));
	rec.setFillColor(sf::Color::Color(0,0,0,200));//������ ����?
	window.draw(rec);
	//---
	cButton->draw(window);
	tButton->draw(window);
	endButton->draw(window);
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