#include "clearscene.h"

ClearScene::ClearScene(){
	font.loadFromFile("font/spike.ttf");
	text.setFont(font); 
	text.setString(L"Game Clear!");
	text.setPosition(450.0f, 250.0f);

	startButton = new Button("img/startButton.png");
	startButton->setPosition(450,400);
	startButton->setText("Back to MainMenu", 18);
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
ClearScene::~ClearScene(){
	delete startButton;
	delete endButton;
}
void ClearScene::update(sf::Event &event){
	startButton->update(event);
	endButton->update(event);

	if(startButton->checkMouseClick(event))
		sceneFlag=true;
	if(endButton->checkMouseClick(event))
		endFlag=true;
}

void ClearScene::draw(sf::RenderWindow &window){
	window.draw(text);
	startButton->draw(window);
	endButton->draw(window);		
}
int ClearScene::changeScene(){
	if(sceneFlag)//시작 버튼을 눌렀을떄
		return 1;
	else if(endFlag)
		return 0;
	return -1;
}