#include "titlescene.h"

TitleScene::TitleScene(){
	font.loadFromFile("font/spike.ttf");
	text.setFont(font); 
	text.setString(L"num1 : Ÿ��Ʋ �� \nnum2 : ���Ӿ� \nnum3 : ���̴���\nnum4 : ����");
	text.setPosition(450.0f, 250.0f);

	particle = new ParticleSystem(600, 600);
	particle->setAngleRange(90, 90);
	particle->setLifeRange(50, 100);
	particle->setStartColor(0, 255, 0, 255);
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
		particle->setLocation(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
		particle->fuelInSequence(0.0, 10);
	}
	particle->draw(window);
	startButton->draw(window);
	endButton->draw(window);		
}
int TitleScene::changeScene(){
	if(sceneFlag)//���� ��ư�� ��������
		return 2;
	else if(endFlag)
		return 0;
	return -1;
}