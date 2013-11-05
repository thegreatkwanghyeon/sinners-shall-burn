#include "stdafx.h"
#include "tileset.h"

using namespace sf;

class Slider{
	private :

		Sprite baseSprite;
		Sprite middleSprite;
		Sprite handleSprite;

		Texture handleTexture;
		Texture tileSetTexture;
		TileSet* tileSet;

		Vector2i position;
		int handlePositionY;

		Vector2i mousePosition;
		int relativeMousePositionX;

		bool controllable;

		float limit;
		float *value;

		void setHandlePosition();
		void setValue();
		float getPercentage();

	public :

		Slider(float *value, String tileSetPath, String handlePath);

		~Slider(){
			delete tileSet;
		}

		void update();
		void draw(RenderWindow &window);

		void setPosition(int x, int y);
		void setLimit(float limit);
};
