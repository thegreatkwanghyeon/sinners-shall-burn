#ifndef __windowentity__
#define __windowentity__

#include "stdafx.h"
#include "tileset.h"

class WindowEntity {
	protected:
		enum Position{ //이것은 텍스쳐를 9 등분 할것인데 그 위치를 알려주는것이다 
			TopLeft,
			Top,
			TopRight,
			Left,
			Center,
			Right,
			BottomLeft,
			Bottom,
			BottomRight,
		};

		sf::Texture texture;
		sf::Sprite sprite[9];
		sf::Vector2f position;

		TileSet *tileset;

		float tooltipWidth;
		float tooltipHeight;

		int individualTextureWidth;
		int individualTextureHeight;

		void defineSpritePositions();
		void defineSpriteScales();

		void setPosition(sf::Vector2f _position);
		void setWindowSize(float _width, float _height);

		float getWidth();

	public:
		WindowEntity(const char *_path);
		virtual ~WindowEntity(){delete tileset;}
		virtual void update();
		virtual void draw(sf::RenderWindow &window);

};

#endif // __windowentity__
