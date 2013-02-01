#ifndef __button__
#define __button__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdio>

#include "tileset.h"

class Button {
	private:

		enum State{
			NormalState, //일반적인 상태
			HoverState,  //마우스 올렸을때
			ClickedState,//클릭되었을때 
			DisableState,//클릭할수 없는 상태일때 
		};

		sf::Sprite    sprite;
		//sf::Sprite    sprites[4];
		sf::Texture   texture;
		sf::Vector2i  position;
		sf::Vector2i  mousePosition;
		sf::IntRect   buttonRect;
		sf::Font      font;
		sf::Text      buttonName;

		TileSet *tileset;
		sf::Keyboard::Key hotkey;

		bool isButtonEnable;

		bool isMouseOver (sf::Vector2i _mousePosition);
		bool isMouseClicked ();



	public:
		Button(sf::String _path);
		~Button(){delete tileset;}
		void update();
		void draw(sf::RenderWindow &window);
		void setPosition(int _x, int _y);
		void setText (sf::String _name, unsigned int _size = 14);
		void enableButton();
		void disableButton();
		bool checkMouseClick();
		void setHotkey(sf::Keyboard::Key _hotkey);

};
#endif