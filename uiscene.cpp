#include "uiscene.h"

UiScene::UiScene(){

	button = new Button("img/button.png");
	button2 = new Button("img/button.png");
	button->setPosition(300,300);
	button->setText("Enabler", 18);
	button->setHotkey(sf::Keyboard::Return);
	button2->setPosition(300,380);
	//button2->setText(L"Ŭ�� �� ������ ĵ");
	button2->disableButton();

	gauge = new Gauge("img/expgauge.png", 5000, 0, 0);
	gauge->setPosition(sf::Vector2i(100,100));
	gauge->setTextElement(18);

	gauge2 = new Gauge("img/hpgauge.png", 5000, 1, 1);
	gauge2->setPosition(sf::Vector2i(100,150));
	gauge2->setTextElement(30);

	tooltip = new Tooltip("img/tooltip.png");
	tooltip->setTooltip(L"��󵵶�!", L"����󵵶�!��(�Ȫ�ɫ�!)�� Ÿ�ɹ̾� �����ڰ� ���� �߽��� �Ϸ���Ʈ�� ���� ����Ʈ �뺧���� �̸� �������� �ϴ� �ִϸ��̼��̴�. �Ϻ������� ���ݹ��� ���Ͽ� 2006�� 3������ ���ǵǾ���, ���ѹα������� �л깮ȭ��(�ͽ�Ʈ�� �뺧)�� ���� 2010�� 4�� ���� ���� 10��(�ϰ�), ���ɿ��� 3�Ǳ��� ���ǵǾ���. ", sf::FloatRect(200,200,300,300), 350);
}

void UiScene::update(){


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

}

void UiScene::draw(sf::RenderWindow &window){
	
	button->draw(window);
	button2->draw(window);

	gauge->draw(window);
	gauge2->draw(window);

	tooltip->draw(window);

}