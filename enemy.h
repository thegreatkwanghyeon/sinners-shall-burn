#ifndef __enemy__
#define __enemy__

#include "stdafx.h"
#include "tinyxml.h"
#include "global.h"
#include "skill.h"

class Enemy{
	private:
		sf::Sprite sprite;
		sf::Image texture;
		sf::String textureName,intro,soundLink;
		std::vector<sf::Uint32> convertedTexture;
		sf::Text name;
		sf::Font font;
		int code;
		int maxHp;
		int damage;//임시
		int currentHp;
		int animationNum;
		int subAniNum;
		int subPro;
		std::vector<Dot> dot;
		int acc,maxAcc;
		sf::Vector2f position;

		TiXmlDocument enemyData;

		std::vector<sf::Uint32> convertImageToTexture(sf::Image image);

		int const textureSize; //텍스처 그림파일 사이즈 (단위 : px)

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

		//임시
		void setPosition(sf::Vector2f position);
		void setTexture(sf::Image texture);
		std::vector<Dot> getDot();
		void addDot(Dot _dot);
		void updateDot();
		void clearDot();
		int getAcc();
		int getSubPro();
		int getSubAni();
		int getMaxAcc();
		void setAcc(int num);
		sf::String getTextureName();
		sf::String getIntro();
		sf::String getSoundLink();
		
};

#endif