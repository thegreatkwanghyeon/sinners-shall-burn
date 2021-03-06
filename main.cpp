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
	//sound.play();
	sound.stop();

	while(window.isOpen()){
		sf::Event Event;
		sound.setVolume(musicVolume);//볼륨 설정

		if(keyEvent && cheatKeyTime.getElapsedTime().asSeconds() >= 0.1){
			keyEvent=false;
		}

		while (window.pollEvent(Event)){
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Insert)){//치트
				cheatButton=true;
				cheatMap=true;
				cheatSkill=true;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)){//치트
				cheatButton=false;
				cheatMap=false;
				cheatSkill=false;
			}
			if(!keyEvent && sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle) && cheatSkillNum < 43){//치트-스킬넘+
				cheatSkillNum++;
				keyEvent=true;
				cheatKeyTime.restart();
			}
			if(!keyEvent && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && cheatSkillNum > 1){//치트-스킬넘-
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

				resetChallenge();//타이틀신으로 올때는 무조건 도전과제 값을 조정한다.
			}
			if(sceneManager->getCurrentScene()->changeScene() == 2){
				view.setViewport(sf::FloatRect(0.f, 0.f, 2.0f, 2.0f));
				sceneManager->setScene(new GameScene());
				//---
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
			if(sceneManager->getCurrentScene()->changeScene() == 4){
				view.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
				sceneManager->setScene(new StoryScene());
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
			_swprintf(stringFps, L"(치트) FPS = %.0f\n맵핵\n퍼즐 재배치 무한\n스킬핵 : %d", fps,cheatSkillNum);
			textFps.setString(stringFps);
			textFps.setCharacterSize(20);
		}

		window.clear();
		window.setView(view);
		sceneManager->update(Event);
		sceneManager->draw(window);

		if(sceneManager->getCurrentScene()->changeScene() == 1){
			view.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
			sceneManager->setScene(new TitleScene());
			//---
			sound.resetBuffer();
			soundBuffer.loadFromFile("sounds/title.wav");
			sound.setBuffer(soundBuffer);
			sound.play();

			resetChallenge();//타이틀신으로 올때는 무조건 도전과제 값을 조정한다.
		}
		if(sceneManager->getCurrentScene()->changeScene() == 2){
			view.setViewport(sf::FloatRect(0.f, 0.f, 2.0f, 2.0f));
			sceneManager->setScene(new GameScene());
			//---
		}
		if(sceneManager->getCurrentScene()->changeScene() == 3){//게임이 끝나는 경우에는 예외적으로 처리함.
			view.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
			sceneManager->setScene(new ClearScene());
			//---
			soundBuffer.loadFromFile("sounds/clear.wav");
			sound.resetBuffer();
			sound.setBuffer(soundBuffer);
			sound.play();
		}

		if(cheatButton)
			window.draw(textFps);
		window.display();


	}
	return EXIT_SUCCESS;
}