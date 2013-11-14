#include "clearscene.h"

ClearScene::ClearScene(){
	font.loadFromFile("font/aPinoL.ttf");
	text.setFont(font); 
	text.setPosition(640.0f, 175.0f);
	text.setCharacterSize(50);
	text.setString(L"Game Clear!");
	text.setOrigin(text.getLocalBounds().width/2,0);

	texture.loadFromFile("img/title.png");
	sprite.setTexture(texture);
	sprite.setPosition(390,150);

	clearTexture.loadFromFile("img/clear.png");
	clearSprite.setTexture(clearTexture);
	//sprite.setPosition(390,150);


	startButton = new Button("img/startButton.png");
	startButton->setPosition(510,400);
	startButton->setText(L"메인화면으로 돌아가기", 18);
	startButton->setClickSound("sounds/button/click.wav");
	startButton->setHoverSound("sounds/button/hover.wav");

	endButton = new Button("img/startButton.png");
	endButton->setPosition(510,500);
	endButton->setText(L"종료", 18);
	endButton->setClickSound("sounds/button/click.wav");
	endButton->setHoverSound("sounds/button/hover.wav");

	sceneFlag=false;
	endFlag=false;

	//printf("your challanges : \nkill : %d/%d\ncoupon : %d/%d\nrebuild : %d\nhint : %d",killEnemyNum,30,getCouponNum,50,useRebuildNum,useHintNum);
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
	sf::Text chText;
	wchar_t plusString[100];
	//---
	window.draw(clearSprite);
	window.draw(sprite);
	window.draw(text);
	startButton->draw(window);
	endButton->draw(window);

	chText.setFont(font);
	chText.setCharacterSize(30);
	chText.setPosition(100,300);
	_swprintf(plusString,L"당신의 플레이 통계 : \n전투 회수 : %d/%d\n얻은 아이템 : %d/%d\n퍼즐 재배치 회수 : %d\n힌트 사용회수 : %d",killEnemyNum,60,getCouponNum,50,useRebuildNum,useHintNum);
	chText.setString(plusString);

	window.draw(chText);
}
int ClearScene::changeScene(){
	if(sceneFlag)//시작 버튼을 눌렀을떄
		return 1;
	else if(endFlag)
		return 0;
	return -1;
}