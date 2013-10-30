#include "titlescene.h"

TitleScene::TitleScene(){
	font.loadFromFile("font/spike.ttf");
	text.setFont(font); 
	text.setString(L"num1 : Å¸ÀÌÆ² ¾À \nnum2 : ²²ÀÓ¾À \nnum3 : ¼ÎÀÌ´õ¾À\nnum4 : ÆÛÁñ");
	text.setPosition(450.0f, 250.0f);

	particle = new ParticleSystem(600, 600);
	particle->setTexture("img/particles/circle.png");
	particle->setAngle(90);
	particle->setAngleVar(90);
	particle->setLife(90);
	particle->setLifeVar(130);
	particle->setSpeed(0.4);
	particle->setSpeedVar(0.6);
	particle->setStartColor(255, 180, 0, 255);
	particle->setEndColor(255, 0, 0, 0);

	startButton = new Button("img/startButton.png");
	startButton->setPosition(450,400);
	startButton->setText("START", 18);
	startButton->setClickSound("sounds/button/click.wav");
	startButton->setHoverSound("sounds/button/hover.wav");

	endButton = new Button("img/startButton.png");
	endButton->setPosition(450,500);
	endButton->setText("END", 18);
	endButton->setClickSound("sounds/button/click.wav");
	endButton->setHoverSound("sounds/button/hover.wav");

	sceneFlag=false;
	endFlag=false;
}
TitleScene::~TitleScene(){
	delete startButton;
	delete endButton;
	delete particle;
}
void TitleScene::update(sf::Event &event){
	particle->update();
	startButton->update(event);
	endButton->update(event);

	if(startButton->checkMouseClick(event))
		sceneFlag=true;
	if(endButton->checkMouseClick(event))
		endFlag=true;
}

void TitleScene::draw(sf::RenderWindow &window){
	window.draw(text);
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		particle->setLocation(sf::Vector2i(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
		particle->setLocationVar(sf::Vector2i(sf::Mouse::getPosition(window).x + 30, sf::Mouse::getPosition(window).y + 30));
		particle->fuelInSequence(0.0, 10);
	}
	particle->draw(window);
	startButton->draw(window);
	endButton->draw(window);		
}
int TitleScene::changeScene(){
	if(sceneFlag)//½ÃÀÛ ¹öÆ°À» ´­·¶À»‹š
		return 2;
	else if(endFlag)
		return 0;
	return -1;
}