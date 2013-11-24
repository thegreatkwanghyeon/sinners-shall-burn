#include "scenemanager.h"
#include "global.h"


int main(void){
	sf::RenderWindow window(sf::VideoMode(1280,720), "SFML");	
	SceneManager *sceneManager = new SceneManager();

	 window.setFramerateLimit(60);
	 sf::Clock clock;
	 sf::Clock cheatKeyTime;
	 bool keyEvent=false;
	 sf::View view;
	 view.reset(sf::FloatRect(0, 0, 1280, 720));
	 float lastTime = 0;

	sf::Sound sound;
	sf::SoundBuffer soundBuffer;

	sound.setLoop(true);
	soundBuffer.loadFromFile("sounds/title.wav");
	sound.setBuffer(soundBuffer);
	sound.play();

	while(window.isOpen()){
		sf::Event Event;
		sound.setVolume(musicVolume);//���� ����

		if(keyEvent && cheatKeyTime.getElapsedTime().asSeconds() >= 0.1){
			keyEvent=false;
		}

		while (window.pollEvent(Event)){
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Insert)){//ġƮ
				cheatButton=true;
				cheatMap=true;
				cheatSkill=true;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)){//ġƮ
				cheatButton=false;
				cheatMap=false;
				cheatSkill=false;
			}
			if(!keyEvent && sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle) && cheatSkillNum < 43){//ġƮ-��ų��+
				cheatSkillNum++;
				keyEvent=true;
				cheatKeyTime.restart();
			}
			if(!keyEvent && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && cheatSkillNum > 1){//ġƮ-��ų��-
				cheatSkillNum--;
				keyEvent=true;
				cheatKeyTime.restart();
			}
			if(Event.type == sf::Event::Closed ||sceneManager->getCurrentScene()->changeScene() == 0){
				window.close();
			}
		
			if(sceneManager->getCurrentScene()->changeScene() == 1){
				view.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
				sceneManager->setScene(new TitleScene());
				//---
				sound.resetBuffer();
				soundBuffer.loadFromFile("sounds/title.wav");
				sound.setBuffer(soundBuffer);
				sound.play();

				resetChallenge();//Ÿ��Ʋ������ �ö��� ������ �������� ���� �����Ѵ�.
			}
			if(sceneManager->getCurrentScene()->changeScene() == 2){
				view.setViewport(sf::FloatRect(0.f, 0.f, 2.0f, 2.0f));
				sceneManager->setScene(new GameScene());
				//---
				sound.resetBuffer();
				soundBuffer.loadFromFile("sounds/gamescene.wav");
				sound.setBuffer(soundBuffer);
				sound.play();
			}
			if(sceneManager->getCurrentScene()->changeScene() == 3){
				view.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
				sceneManager->setScene(new ClearScene());
				//---
				sound.resetBuffer();
				soundBuffer.loadFromFile("sounds/clear.wav");
				sound.setBuffer(soundBuffer);
				sound.play();
			}
			sceneManager->update(Event);
		}

		float currentTime = clock.restart().asSeconds();
        float fps = 1.f / currentTime ;
        lastTime = currentTime;

		sf::Text textFps;
		sf::Font font;
		wchar_t stringFps[20];

		font.loadFromFile("font/aPinoL.ttf");
		textFps.setFont(font);
		if(cheatButton){
			_swprintf(stringFps, L"(ġƮ) FPS = %.0f\n����\n���� ���ġ ����\n��ų�� : %d", fps,cheatSkillNum);
			textFps.setString(stringFps);
		}else{
			_swprintf(stringFps, L"FPS = %.0f", fps);
			textFps.setString(stringFps);
		}
		textFps.setCharacterSize(20);	

		window.clear();
		window.setView(view);
		sceneManager->update(Event);
		sceneManager->draw(window);
		if(sceneManager->getCurrentScene()->changeScene() == 3){//������ ������ ��쿡�� ���������� ó����.
			view.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
			sceneManager->setScene(new ClearScene());
			//---
			soundBuffer.loadFromFile("sounds/clear.wav");
			sound.resetBuffer();
			sound.setBuffer(soundBuffer);
			sound.play();
		}

		window.draw(textFps);
		window.display();


	}
	return EXIT_SUCCESS;
}