#include "pause.h"

Pause::Pause(){
	isPause=false;
	endFlag=false;
	titleFlag=false;
	
	font.loadFromFile("font/aPinoL.ttf");
	fText.setFont(font);
	fText.setPosition(640.0f, 65.0f);
	fText.setCharacterSize(80);
	fText.setString(sf::String(L"일시정지"));
	fText.setOrigin(fText.getLocalBounds().width/2,0);

	texture.loadFromFile("img/title.png");
	sprite.setTexture(texture);
	sprite.setPosition(390,50);

	cButton = new Button("img/startbutton.png");
	cButton->setClickSound("sounds/button/click.wav");
	cButton->setHoverSound("sounds/button/hover.wav");
	cButton->setPosition(510,200);
	cButton->setText(L"게임으로 돌아가기");

	tButton = new Button("img/startbutton.png");
	tButton->setClickSound("sounds/button/click.wav");
	tButton->setHoverSound("sounds/button/hover.wav");
	tButton->setPosition(510,450);
	tButton->setText(L"메인화면으로 돌아가기");

	endButton = new Button("img/startbutton.png");
	endButton->setClickSound("sounds/button/click.wav");
	endButton->setHoverSound("sounds/button/hover.wav");
	endButton->setPosition(510,550);
	endButton->setText(L"게임 종료");

	slider = new Slider(&soundVolume, "img/slider/slider.png", "img/slider/handle.png");
	slider->setPosition(390,390);
	slider->setLimit(100);

	bgmSlider = new Slider(&musicVolume, "img/slider/slider.png", "img/slider/handle.png");
	bgmSlider->setPosition(390,300);
	bgmSlider->setLimit(100);
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
	bgmSlider->update();
	if(cButton->checkMouseClick(event))
		pauseOff();//콘티뉴버튼 누르면 계속 진행...
	if(endButton->checkMouseClick(event))
		endFlag=true;
	if(tButton->checkMouseClick(event))
		titleFlag=true;
}
void Pause::draw(sf::RenderWindow &window){
	sf::RectangleShape rec;//화면 검게 덮어줄 사각형
	sf::Text text;
	rec.setPosition(0,0);
	rec.setSize(sf::Vector2f(1280,720));
	rec.setFillColor(sf::Color::Color(0,0,0,200));//반투명 검정?
	window.draw(rec);
	//---
	cButton->draw(window);
	tButton->draw(window);
	endButton->draw(window);
	slider->draw(window);
	bgmSlider->draw(window);

	window.draw(sprite);
	window.draw(fText);

	text.setFont(font);

	text.setString("BGM");
	text.setPosition(640,260);
	text.setOrigin(text.getLocalBounds().width/2,0);
	window.draw(text);
	text.setString("SOUND");
	text.setPosition(640,350);
	text.setOrigin(text.getLocalBounds().width/2,0);
	window.draw(text);
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