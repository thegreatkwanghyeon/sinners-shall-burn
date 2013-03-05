#include "uiscene.h"

UiScene::UiScene(){

	button = new Button("img/button.png");
	button2 = new Button("img/button.png");
	button->setPosition(300,300);
	button->setText("Enabler", 18);
	button->setHotkey(sf::Keyboard::Return);
	button2->setPosition(300,380);
	button2->setText(L"클릭 미 이프유 캔",14);
	button2->disableButton();

	gauge = new Gauge("img/expgauge.png", 5000, 0, 0);
	gauge->setPosition(sf::Vector2i(100,100));
	gauge->setTextElement(18);

	gauge2 = new Gauge("img/hpgauge.png", 5000, 1, 1);
	gauge2->setPosition(sf::Vector2i(100,150));
	gauge2->setTextElement(30);

	tooltip = new Tooltip("img/tooltip.png");
	tooltip->setTooltip(L"토라도라!", L"《토라도라!》(とらドラ!)는 타케미야 유유코가 쓰고 야스가 일러스트를 맡은 라이트 노벨이자 이를 원작으로 하는 애니메이션이다. 일본에서는 전격문고를 통하여 2006년 3월부터 출판되었고, 대한민국에서는 학산문화사(익스트림 노벨)를 통해 2010년 4월 현재 본편 10권(완결), 스핀오프 3권까지 출판되었다. ", sf::FloatRect(200,200,300,300), 350);

	dialog = new Dialog("img/tooltip.png");
	dialog->setScript(L"야, 이 반란군 놈의 새끼야! 니들 거기 꼼짝 말고 있어! 내가 지금 전차를 몰고 가서 네놈들의 머리통을 다 날려버리겠어!");
	dialog->setScript(L"계란을 주먹으로 꽉 쥐어서 깨트릴 사람은 지구상에 존재하지 않는다. 따라서 그것을 쥐어서 압력을 받은 뒤 가격한다면,엄청난 타격이 된다. 풍호는 언제나 달걀을 가지고 다닌다. 따라서 그의 싸움 뒤에는 ,김이 모락모락 나는 2개 으깨진 노른자가 항상 있는 것이다.");

}

void UiScene::update(sf::Event &event){


	button->update();
	button2->update();
	if(button->checkMouseClick()){
		button2->enableButton();
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		gauge->setValue(+1);
		gauge2->setValue(+1);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
		gauge->setValue(-1);
		gauge2->setValue(-1);
	}

	gauge->update();
	gauge2->update();

	tooltip->update();

	dialog->update();

}

void UiScene::draw(sf::RenderWindow &window){
	
	button->draw(window);
	button2->draw(window);

	gauge->draw(window);
	gauge2->draw(window);

	tooltip->draw(window);

	dialog->draw(window);
}