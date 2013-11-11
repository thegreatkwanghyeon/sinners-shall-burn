#include "titlescene.h"
#include "global.h"

/*
주석달린 부분들은 파티클(현재의 스킬이펙트) 테스트를 위한 코드.
차후 디콘 설명서 작성이나 기타 시연등에 필요함을 고려,
주석으로 처리하였음.
*/

TitleScene::TitleScene(){/*
	particle = new ParticleList(640,200);
	particle->setParticle(1,"",false);
	pNum=1;
	isPress=false;
	printf("particle : %d\n",pNum);
	skill = new Skill();*/

	startButton = new Button("img/startButton.png");
	startButton->setPosition(250,500);
	startButton->setText("START", 18);
	startButton->setClickSound("sounds/button/click.wav");
	startButton->setHoverSound("sounds/button/hover.wav");

	endButton = new Button("img/startButton.png");
	endButton->setPosition(760,500);
	endButton->setText("END", 18);
	endButton->setClickSound("sounds/button/click.wav");
	endButton->setHoverSound("sounds/button/hover.wav");

	//startButton->setPosition(510,400);
	//endButton->setPosition(510,500);

	slider = new Slider(&soundVolume, "img/slider/slider.png", "img/slider/handle.png");
	slider->setPosition(500, 300);
	slider->setLimit(100);

	lightning = new Lightning();
	lightning->setDetail(3);
	lightning->setDisplacement(150);
	lightning->setThcikness(2);
	lightning->setStartPosition(100, 100);
	lightning->setEndPosition(700, 300);
	lightning->setColor(100, 200, 255);

	sceneFlag=false;
	endFlag=false;

	texture.loadFromFile("img/titleimage.png");
	sprite.setTexture(texture);
	sprite.setPosition(0,0);
}
TitleScene::~TitleScene(){
	delete startButton;
	delete endButton;
	//delete particle;
}
void TitleScene::update(sf::Event &event){
	/*
	particle->update();
	if(!isPress && sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) && pNum > 1){
		pNum--;
		isPress=true;
		pTime.restart();
		particle->setParticle(pNum,"",false);
		printf("particle : %d\n",pNum);
	}
	if(!isPress && sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)){
		pNum++;
		isPress=true;
		pTime.restart();
		particle->setParticle(pNum,"",false);
		printf("particle : %d\n",pNum);
	}

	if(isPress && pTime.getElapsedTime().asSeconds() >= 0.1)
		isPress=false;*/

	startButton->update(event);
	endButton->update(event);
	slider->update();
	lightning->update();

	if(startButton->checkMouseClick(event))
		sceneFlag=true;
	if(endButton->checkMouseClick(event))
		endFlag=true;
}

void TitleScene::draw(sf::RenderWindow &window){
	sf::Font font;
	sf::Text skillName;
	sf::Texture texture;
	sf::Sprite icon;

	window.draw(sprite);
	//---
	/*
	font.loadFromFile("font/aPinoL.ttf");
	skillName.setFont(font);
	skillName.setString(skill->data[pNum].name);
	skillName.setPosition(0,300);
	window.draw(skillName);

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		particle->setLocationList();
	}
	particle->draw(window);	
	slider->draw(window);
	lightning->draw(window);
	
	icon.setPosition(200,200);
	texture.loadFromFile(skill->data[pNum].link);
	icon.setTexture(texture);
	window.draw(icon);*/
	//---
	startButton->draw(window);
	endButton->draw(window);
}
int TitleScene::changeScene(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		return 0;
	if(sceneFlag)//시작 버튼을 눌렀을떄
		return 2;
	else if(endFlag)
		return 0;
	return -1;
}