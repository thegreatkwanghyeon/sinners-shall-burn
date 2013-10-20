#ifndef __gauge__
#define __gauge__

#include "stdafx.h"

#include "tileset.h"

class Gauge {
	private:
		sf::Sprite middleSprite;
		sf::Sprite baseSprite;
		sf::Sprite coverSprite;
		sf::Texture texture;
		sf::Vector2i position;
		//sf::IntRect gaugeRect;
		sf::Font font;
		sf::Text text;

		TileSet *tileset;

		float gaugeValue;
		float gaugeLimit;

		int gaugeType; //0�̸� ���� 1�̸� ���� 
		int textPercentage; //0�̸� ���ڷ� 1�̸� �ۼ�Ʈ�� ������

		void setGaugeTextureRect();
		void setText();


	public:
		Gauge(sf::String _path, float _limit, int _gaugeType = 0, int _textPercentage = 0);
		~Gauge(){delete tileset;}
		void update();
		void draw(sf::RenderWindow &window);
		void setValue(float _value);
		void setPosition(sf::Vector2i _position);
		void setTextElement(int _textSize, sf::Color _textColor = sf::Color(255,255,255));

		float getValue();
};

#endif