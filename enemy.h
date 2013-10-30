#ifndef __enemy__
#define __enemy__

#include "stdafx.h"
#include "tinyxml.h"
#include "global.h"

class Enemy{
	private:
		sf::Sprite sprite;
		sf::Image texture;
		std::vector<sf::Uint32> convertedTexture;
		sf::Text name;
		sf::Font font;
		int code;
		int maxHp;
		int damage;//�ӽ�
		int currentHp;
		int animationNum;
		int subAniNum;
		int subPro;
		int dot;
		int acc;
		sf::Vector2f position;

		TiXmlDocument enemyData;

		std::vector<sf::Uint32> convertImageToTexture(sf::Image image);

		int const textureSize; //�ؽ�ó �׸����� ������ (���� : px)

	public:
		Enemy();
		Enemy(int code);
		~Enemy();

		sf::Text getName();
		int getMaxHp();
		int getDamage();
		int getAnimationNum();
		int getCurrentHp();
		void setCurrentHp(int num);
		sf::Vector2f getPosition();
		sf::Sprite getSprite();
		sf::Image getTexture();
		int getCode();
		std::vector<sf::Uint32>* getConvertedTexture();

		//�ӽ�
		void setPosition(sf::Vector2f position);
		void setTexture(sf::Image texture);
		int getDot();
		void setDot(int num);
		int getAcc();
		int getSubPro();
		int getSubAni();

		
};

#endif