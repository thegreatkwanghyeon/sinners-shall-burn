#include "titlescene.h"
#include "global.h"

TitleScene::TitleScene(){
	font.loadFromFile("font/spike.ttf");
	text.setFont(font); 
	text.setString(L"num1 : Å¸ÀÌÆ² ¾À \nnum2 : ²²ÀÓ¾À \nnum3 : ¼ÎÀÌ´õ¾À\nnum4 : ÆÛÁñ");
	text.setPosition(450.0f, 250.0f);

	particle = new ParticleList(640,200);
	particle->setParticle(1);
	pNum=1;
	isPress=false;
	printf("particle : %d\n",pNum);
	skill = new Skill();

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

	slider = new Slider(&soundVolume, "img/slider/slider.png", "img/slider/handle.png");
	slider->setPosition(500, 300);
	slider->setLimit(100);

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
	if(!isPress && sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) && pNum > 1){
		pNum--;
		isPress=true;
		pTime.restart();
		particle->setParticle(pNum);
		printf("particle : %d\n",pNum);
	}
	if(!isPress && sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)){
		pNum++;
		isPress=true;
		pTime.restart();
		particle->setParticle(pNum);
		printf("particle : %d\n",pNum);
	}

	if(isPress && pTime.getElapsedTime().asSeconds() >= 0.5)
		isPress=false;

	startButton->update(event);
	endButton->update(event);
	slider->update();

	if(startButton->checkMouseClick(event))
		sceneFlag=true;
	if(endButton->checkMouseClick(event))
		endFlag=true;
}

void TitleScene::draw(sf::RenderWindow &window){
	sf::Text skillName;

	skillName.setFont(font);
	skillName.setString(skill->data[pNum].name);
	skillName.setPosition(0,300);
	window.draw(skillName);

	window.draw(text);
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		particle->setLocationList();
	}
	particle->draw(window);
	startButton->draw(window);
	endButton->draw(window);	
	slider->draw(window);
}
int TitleScene::changeScene(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		return 0;
	if(sceneFlag)//½ÃÀÛ ¹öÆ°À» ´­·¶À»‹š
		return 2;
	else if(endFlag)
		return 0;
	return -1;
}